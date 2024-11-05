#include <fstream>    
#include <sstream>
#include <cstdio>

#include <chrono>
#include <ctime>      

#include <random>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
#include <cstring>

#include "account.h"
#include "card.h"  // Include Private Card Children

void Account::Run() noexcept
{
    try 
    {
        if (!fn_DB_Exist(DB)) 
        { 
            printf("Warning: Database not found. Creating new database.\n");
            std::ofstream file("2B.txt");
            file.close();
        }

        fn_Create_Account();
        fn_Set_Card_Details();
        fn_Show_Card_Details();
        fn_Save_To_DB();
    }
    catch (const std::exception& e) 
    {
        printf("Error during account setup: %s\n", e.what());
    }
}

void Account::fn_Create_Account()
{
    system("cls");
    try 
    {
        card = std::make_unique<Card>();
        Account_ID = fn_Gen_Card_Number();
        printf("=== Create New Account ===\n\n");
    }
    catch (const std::bad_alloc& e) 
    {
        printf("Failed to create account: %s\n", e.what());
        throw;
    }
}

bool Account::fn_Login()
{
    system("cls");
    printf("=== Login ===\n\n");
    try 
    {
        // Get and validate card number input
        char input_card_number[Constants::CARD_NUMBER_LENGTH];

        printf("Enter your card number: ");
        if (scanf_s("%s", input_card_number, (char*)(sizeof(input_card_number))) != 1) 
        {
            printf("Invalid card number format.\n");
            while (getchar() != '\n');
            return false;
        }
        while (getchar() != '\n');

        // Clean card number input
        std::string cleaned_input;
        for (size_t i = 0; input_card_number[i] != '\0'; ++i) 
        {
            if (input_card_number[i] != '_') 
            {
                cleaned_input += input_card_number[i];
            }
        }

        // Get and validate PIN input
        char pin_str[Constants::PIN_LENGTH + 2];

        printf("Enter your PIN: ");
        if (scanf_s("%s", pin_str, (char*)(sizeof(pin_str))) != 1) 
        {
            printf("Invalid PIN format.\n");
            while (getchar() != '\n');
            return false;
        }
        while (getchar() != '\n');

        // Convert PIN to number
        uint_fast16_t input_pin;
        try 
        {
            input_pin = (uint_fast16_t)(std::stoi(pin_str));
        } 
        catch (const std::exception&) 
        {
            printf("Invalid PIN format.\n");
            return false;
        }

        // Read from database
        std::ifstream file(DB);
        if (!file) 
        {
            throw std::runtime_error("Could not open database file");
        }

        std::string line;
        bool in_account_block = false;
        bool found_account = false;
        std::streampos account_block_start;

        // Search for matching account
        while (std::getline(file, line)) 
        {
            if (line.find("=====================") != std::string::npos) {
                account_block_start = file.tellg();
                in_account_block = true;
                continue;
            }

            if (in_account_block) 
            {
                if (line.find("Account ID: ") != std::string::npos) 
                {
                    Account_ID = std::stoull(line.substr(11)); // substr(11) to skip "Account ID: " as it = 11 chars, same for other lines
                }
                else if (line.find("Card Number: ") != std::string::npos) 
                {
                    std::string temp_card_number = line.substr(13);
                    std::string cleaned_stored;
                    for (char c : temp_card_number) 
                    {
                        if (c != '_') 
                        {
                            cleaned_stored += c;
                        }
                    }
                    
                    // If card number matches, load all account details
                    if (cleaned_stored == cleaned_input) 
                    {
                        card = std::make_unique<Card>();
                        strncpy_s(card->Card_number, temp_card_number.c_str(), sizeof(card->Card_number) - 1);
                        found_account = true;
                        
                        // Go back to start of account block and read all details
                        file.seekg(account_block_start);

                        while (std::getline(file, line)) 
                        {
                            // Stop at the end of the account block
                            if (line.find("=====================") != std::string::npos && found_account) 
                            {
                                break;
                            }
                            
                            if (line.find("Owner Name: ") != std::string::npos) {
                                strncpy_s(card->Owner_name, line.substr(11).c_str(), sizeof(card->Owner_name) - 1);
                            }
                            else if (line.find("Owner Surname: ") != std::string::npos) {
                                strncpy_s(card->Owner_Surname, line.substr(14).c_str(), sizeof(card->Owner_Surname) - 1);
                            }
                            else if (line.find("PIN: ") != std::string::npos) {
                                card->m_PIN = (uint_fast16_t)(std::stoi(line.substr(5)));
                            }
                            else if (line.find("SCV: ") != std::string::npos) {
                                card->m_SCV = (uint_fast16_t)(std::stoi(line.substr(5)));
                            }
                        }
                        break;
                    }
                }
            }

            if (line.empty()) {
                in_account_block = false;
            }
        }

        file.close();

        // Verify credentials
        if (!found_account) 
        {
            printf("Card number not found.\n");
            return false;
        }

        if (card->m_PIN != input_pin) 
        {
            printf("Incorrect PIN.\n");
            return false;
        }

        printf("Login successful!\n");
        return true;
    }
    catch (const std::exception& e) 
    {
        printf("Login error: %s\n", e.what());
        return false;
    }
}

// ------------------------- CARD -------------------

uint_fast64_t Account::fn_Gen_Card_Number()
{
    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_int_distribution<uint_fast64_t> dist(0, Constants::MAX_CARD_NUMBER);

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

    strncpy_s(card->Card_number, formatted.str().c_str(), sizeof(card->Card_number) - 1);

    return formatted.str();
}

void Account::fn_Set_Card_Details()
{
    if (!card) 
    {
        throw std::runtime_error("Card not initialized");
    }

    fn_Transfer_Card_Number();

    fn_set_Card_Names(card->Owner_name, "Set card.Owner_Name");
    fn_set_Card_Names(card->Owner_Surname, "Set card.Owner_Surname");

    card->m_PIN = fn_Set_Pin();

    do 
    {
        printf("Set card.SCV (3 digits): ");
        scanf_s("%u", &card->m_SCV);
        while (getchar() != '\n');
    } 
    while (!fn_ValidateNums(card->m_SCV, 3, 3));
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

        pin = (uint_fast16_t)(atoi(input));
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

void Account::fn_Show_Card_Details()
{
    system("cls");
    card->Show_Card_Details();
}

// ------------------------- VALIDATION -------------------

bool Account::fn_ValidateInput(char(&input)[Constants::NAME_SIZE], uint_fast8_t maxLength, uint_fast8_t minLength) const
{
    if (input[0] == '\0') 
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
        if (!isalpha((char)(input[i]))) {
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

    std::ifstream file(DB);
    return file.good();
}

// ------------------------- BALANCE -------------------

bool Account::Deposit(double amount) noexcept
{
    return balance.Deposit(amount, Account_ID);
}

bool Account::Withdraw(double amount) noexcept
{
    return balance.Withdraw(amount, Account_ID);
}

double Account::Get_Balance() const noexcept
{
    return balance.Get_Balance(Account_ID);
}

// ------------------------- DB -------------------

void Account::fn_Save_To_DB() const
{
    try 
    {
        std::ofstream file(DB, std::ios::app);
        if (!file)
        {
            throw std::runtime_error("Could not open database file");
        }

        // Get current time
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        char time_str[26];
        ctime_s(time_str, sizeof(time_str), &time);
        
        file << "=====================\n";
        file << "Account Created: " << time_str;
        file << "Account ID: " << Account_ID << "\n";
        
        // Save non-sensitive data
        file << "Owner Name: " << card->Owner_name << "\n";
        file << "Owner Surname: " << card->Owner_Surname << "\n";
        
        // Save sensitive data
        file << "Card Number: " << card->Card_number << "\n";
        file << "PIN: " << card->m_PIN << "\n";  // In production, this should be hashed
        file << "SCV: " << card->m_SCV << "\n";  // In production, this should be encrypted
        file << "Initial Balance: " << balance.GetCurrentBalance() << "\n";
        file << "=====================\n\n";

        file.close();
    }
    catch (const std::exception& e)
    {
        printf("Failed to save to database: %s\n", e.what());
        throw;
    }
}