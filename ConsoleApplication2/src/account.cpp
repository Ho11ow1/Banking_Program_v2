#include <filesystem>
#include <random>

#include "account.h"
#include "card.h"  // Include Card.h

void Account::Create_Account()
{
    // Allocate memory for card
    card = new Card(); //unique_ptr should do this

    /*std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<uint_fast8_t> dist(0, 255);

    Account_ID = dist(mt);*/

    printf("%s", "Created account\n");
}

uint_fast64_t Account::Gen_Card_Number()
{
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<uint_fast64_t> dist(0, 999999999999);

    return dist(mt);
}

std::string Account::Transfer_Card_Number()
{
    std::string formattedNumber = "";
    uint_fast64_t cardNumber = Gen_Card_Number();
    std::string cardNumberStr = std::to_string(cardNumber);

    for (size_t i = 0; i < cardNumberStr.length(); ++i)
    {
        formattedNumber += cardNumberStr[i];
        if ((i + 1) % 3 == 0 && i != cardNumberStr.length() - 1)
        {
            formattedNumber += "_";
        }
    }

    // Ensure card is allocated
    if (card != nullptr)
    {
        strncpy_s(card->Card_number, formattedNumber.c_str(), sizeof(card->Card_number) - 1); // Dest, src, sizeof(dest) -(\0 null term)
    }

    return formattedNumber;
}

void Account::Set_Card_Details()
{
    Transfer_Card_Number();

    if (card != nullptr)
    {
        //Owner_name
        while (!ValidateInput(card->Owner_name, 24, 3)) 
        {
            printf("Set card.Owner_Name(Max 24 characters): ");
            fgets(card->Owner_name, 25, stdin); // Read name + \0 ---------- Prevent a buffer overflow
            card->Owner_name[strcspn(card->Owner_name, "\n")] = '\0'; // Change \n from fgets to \0
        }

        // Owner Surname
        while (!ValidateInput(card->Owner_Surname, 24, 3)) 
        {
            printf("Set card.Owner_Surname(Max 24 characters): ");
            fgets(card->Owner_Surname, 25, stdin);
            card->Owner_Surname[strcspn(card->Owner_Surname, "\n")] = '\0';
            /*scanf_s("%24s", card->Owner_Surname, (unsigned)_countof(card->Owner_Surname));*/
        }

        // PIN
        //while (!ValidateNums(card->m_PIN, 4, 4))
        //{
        //    printf("Set card.PIN (4 digits): ");
        //    scanf_s("%hu", (uint_fast16_t*)&card->m_PIN);
        //    //Set_Pin();
        //}

        /*printf("Set card.PIN(Max 4 Digits): ");
        scanf_s("%hu", (uint16_t*)&card->m_PIN);

        printf("Set card.SCV(Max 3 Digits): ");
        scanf_s("%hu", (uint16_t*)&card->m_SCV);*/
        
    }
}

uint_fast16_t Account::Set_Pin()
{
    while (1) // Change this
    {
        char input[5];
        printf("Set card.PIN (4 digits): ");
        fgets(input, 5, stdin);

        if (strlen(input) != 5)
        {
            printf("Invalid PIN length. Please enter 4 digits.\n");
            continue; // return to the top
        }

        uint_fast32_t* temp{};

        card->m_PIN = (uint_fast16_t)temp;
    }
}

bool Account::ValidateInput(char(&input)[25], uint_fast8_t maxLength, uint_fast8_t minLength)
{
    int length = strlen(input);
    if (length <= maxLength && length >= minLength) 
    {
        return true; // Valid input
    }
    else 
    {
        //while (getchar() != '\n'); // No need for this because of fgets
        //printf("%s%hhu%s%hhu%s\n", "Input must be at most ", maxLength, " characters long and at least ", minLength, " characters long, please try again.");
        printf("Input must be at most %hhu characters long and at least %hhu characters long, please try again.\n", maxLength, minLength); // Revised version

        return false; // Invalid input
    }
}

bool Account::ValidateNums(uint_fast16_t& input, uint_fast16_t MaxSize, uint_fast16_t MinSize)
{
    if (input >= MinSize && input <= MaxSize)
    {
        return true; // Valid input
    }
    else
    {
        //printf("Invalid PIN or SCV.  Must be between %hu and %hu.\n", MinSize, MaxSize);
        printf("Invalid PIN or SCV. Must be between %hu and %hu.\n", MinSize, MaxSize); // Revised version
        return false; // Invalid input
    }
}

void Account::Show_Card_Details()
{
    if (card != nullptr)
    {
        printf("\nCard_Owner_Name: %s\n", card->Owner_name);
        printf("Card_Owner_Surname: %s\n", card->Owner_Surname);
        printf("Card_number: %s\n", card->Card_number);
        printf("Card_PIN: %hu\n", card->m_PIN);
        printf("Card_SCV: %hu\n", card->m_SCV);
    }
}
