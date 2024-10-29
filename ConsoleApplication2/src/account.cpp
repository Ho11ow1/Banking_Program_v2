#include <fstream>
#include <sstream>

#include "account.h"
#include "card.h"  // Include Private Card Children

void Account::Run() noexcept
{
    try 
    {
        // Check if database exists
        if (!fn_DB_Exist(DB)) 
        { 
            printf("Warning: Database not found. Creating new database.\n");
            std::ofstream file("2B.txt");
            file.close();
        }

        fn_Create_Account();
        fn_Set_Card_Details();
        fn_Show_Card_Details();
    }
    catch (const std::exception& e) 
    {
        printf("Error during account setup: %s\n", e.what());
    }
}

void Account::fn_Create_Account()
{
    try 
    {
        card = std::make_unique<Card>();
        printf("Created account\n\n");
    }
    catch (const std::bad_alloc& e) 
    {
        printf("Failed to create account: %s\n", e.what());
        throw;
    }
}

uint_fast64_t Account::fn_Gen_Card_Number()
{
    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_int_distribution<uint_fast64_t> dist(0, MAX_CARD_NUMBER);

    return dist(mt);
}

std::string Account::fn_Transfer_Card_Number()
{
    if (!card) 
    {
        throw std::runtime_error("Card not initialized");
    }

    std::ostringstream formatted;
    std::string cardNumberStr = std::to_string(fn_Gen_Card_Number());
    
    for (size_t i = 0; i < cardNumberStr.length(); ++i) 
    {
        formatted << cardNumberStr[i];
        if ((i + 1) % 4 == 0 && i != cardNumberStr.length() - 1) 
        {
            formatted << '_';
        }
    }

    if (card) 
    {
        strncpy_s(card->Card_number, formatted.str().c_str(), sizeof(card->Card_number) - 1);
    }

    return formatted.str();
}

void Account::fn_Set_Card_Details()
{
    if (!card) 
    {
        throw std::runtime_error("Card not initialized");
    }

    fn_Transfer_Card_Number();

    // Set PIN
    card->m_PIN = fn_Set_Pin();

    // Set SCV
    do 
    {
        printf("Set card.SCV (3 digits): ");
        scanf_s("%u", &card->m_SCV);
        while (getchar() != '\n'); // Clear input buffer
    } 
    while (!fn_ValidateNums(card->m_SCV, 3, 3));

    fn_set_Card_Names(card->Owner_name, "Set card.Owner_Name");
    fn_set_Card_Names(card->Owner_Surname, "Set card.Owner_Surname");
}

uint_fast16_t Account::fn_Set_Pin()
{
    constexpr int PIN_LENGTH = 4;
    char input[PIN_LENGTH + 2];  // +2 for newline and null terminator
    uint_fast16_t pin;
    
    while (true) 
    {
        printf("Set card.PIN (%d digits): ", PIN_LENGTH);
        if (!fgets(input, sizeof(input), stdin)) 
        {
            continue;
        }

        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        // Check if input is exactly PIN_LENGTH digits
        if (strlen(input) != PIN_LENGTH) 
        {
            printf("PIN must be exactly %d digits.\n", PIN_LENGTH);
            continue;
        }

        // Check if all characters are digits
        bool valid = true;
        for (int i = 0; i < PIN_LENGTH; i++) 
        {
            if (!isdigit(input[i])) 
            {
                valid = false;
                break;
            }
        }

        if (!valid)
        {
            printf("PIN must contain only digits.\n");
            continue;
        }

        pin = static_cast<uint_fast16_t>(atoi(input));
        return pin;
    }
}

void Account::fn_set_Card_Names(char(&destination)[Constants::NAME_SIZE], const char* prompt) noexcept
{
    do 
    {
        printf("%s (3-24 characters): ", prompt);
        if (fgets(destination, Constants::NAME_SIZE, stdin)) 
        {
            size_t len = strlen(destination);
            if (len > 0 && destination[len-1] == '\n') 
            {
                destination[len-1] = '\0';
                len--;
            }

            if (len > Constants::MAX_NAME_LENGTH) 
            {
                printf("Input is too long (maximum %d characters).\n", Constants::MAX_NAME_LENGTH);
                continue;
            }
        }
    } 
    while (!fn_ValidateInput(destination, Constants::MAX_NAME_LENGTH, Constants::MIN_NAME_LENGTH));
}

void Account::fn_Show_Card_Details() const
{
    if (!card)
    {
        throw std::runtime_error("Card not initialized");
    }

    card->Show_Card_Details();
}

// ------------------------- CHECKERS -------------------

bool Account::fn_ValidateInput(char(&input)[Constants::NAME_SIZE], uint_fast8_t maxLength, uint_fast8_t minLength) const
{
    if (!input) 
    {
        return false;
    }

    size_t length = strlen(input);
    
    if (length < minLength || length > maxLength) 
    {
        printf("Input must be between %hhu and %hhu characters long.\n", minLength, maxLength);
        return false;
    }

    for (size_t i = 0; i < length; i++) 
    {
        if (!isalpha(static_cast<unsigned char>(input[i]))) {
            printf("Input must contain only letters.\n");
            return false;
        }
    }
    return true;
}

bool Account::fn_ValidateNums(uint_fast16_t& input, uint_fast16_t MaxSize, uint_fast16_t MinSize) const
{
    uint_fast16_t nums{0};
    uint_fast16_t temp{input};  // Initialize from input

    do 
    {
        nums++;
        temp /= 10;
    } 
    while (temp > 0);

    if (nums >= MinSize && nums <= MaxSize) 
    {
        return true;
    }

    printf("Number must be between %hu and %hu digits.\n", MinSize, MaxSize);
    return false;
}

bool Account::fn_DB_Exist(const char(&DB)[Constants::MAX_DB_NAME]) const
{
    if (DB[0] == '\0') 
    {
        return false;
    }
    
    try
    {
        std::ifstream file(DB);
        bool exists = file.good();
        file.close();
        return exists;
    }
    catch(const std::exception& e)
    {
        printf("Error checking DB: %s\n", e.what());
        return false;
    }

}