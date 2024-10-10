#include <filesystem>
#include <random>

#include "card.h"

uint_fast64_t Card::Gen_Card_Number()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<uint_fast64_t> dist(0, 999999999999);

    return dist(mt);
}

std::string Card::Transfer_Card_Number()
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

    strncpy_s(card.Card_number, formattedNumber.c_str(), sizeof(card.Card_number) - 1); // Dest, src, sizeof(dest) -(\0 null term)

    return formattedNumber;
}

void Card::Set_Card_Details()
{
    Transfer_Card_Number();

    printf("Set card.Owner_Name(Max 24 characters): ");
    scanf_s("%24s", card.Owner_name, (unsigned)_countof(card.Owner_name));

    printf("Set card.Owner_SurName(Max 24 characters): ");
    scanf_s("%24s", card.Owner_Surname, (unsigned)_countof(card.Owner_Surname)); // Sizeof() / Sizeof([0])

    printf("Set card.PIN: ");
    scanf_s("%hu", (uint16_t*)&card.m_PIN);

    printf("Set card.SCV: ");
    scanf_s("%hu", (uint16_t*)&card.m_SCV);
}

void Card::Show_Card_Details()
{
    printf("\nCard_Owner_Name: %s\n", card.Owner_name);
    printf("Card_Owner_Surname: %s\n", card.Owner_Surname);

    printf("Card_number: %s\n", card.Card_number);
    printf("Card_PIN: %hu\n", card.m_PIN);
    printf("Card_SCV: %hu\n", card.m_SCV);
}
