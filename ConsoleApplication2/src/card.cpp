#include <filesystem>
#include <random>

#include <sstream>
#include "card.h"

void Card::Gen_Card_Number()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<uint_fast64_t> dist(0, 999999999999);
    Card_number = dist(mt);
}

void Card::Show_Card_Number()
{
    std::string formattedNumber = "";

    std::string cardNumberStr = std::to_string(Card_number);

    for (size_t i = 0; i < cardNumberStr.length(); ++i)
    {
        formattedNumber += cardNumberStr[i];
        if ((i + 1) % 3 == 0 && i != cardNumberStr.length() - 1)
        {
            formattedNumber += "'";
        }
    }

    printf("%s", formattedNumber.c_str());
}