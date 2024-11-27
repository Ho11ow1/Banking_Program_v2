#include <cstring>

#include "./validation.h"
#include "../constants.h"

std::string Validation::GetValidInput(std::string prompt)
{
    std::string str;
    do
    {
        printf("%s (%hhd-%hhd characters): ", prompt.c_str(), Constants::MIN_NAME_LENGTH, Constants::MAX_NAME_LENGTH);

        char buffer[Constants::MAX_NAME_LENGTH + 1];
        fgets(buffer, Constants::MAX_NAME_LENGTH + 1, stdin);
        str = buffer;
    } 
    while (!ValidateInput(str, Constants::MIN_NAME_LENGTH, Constants::MAX_NAME_LENGTH));

    return str;
}

bool Validation::ValidateInput(std::string input, uint_fast8_t minLength, uint_fast8_t maxLength)
{
    if (input.empty())
    {
        printf("Input cannot be empty.\n");
        return false;
    }
    if (!IsValid(input))
    {
        printf("Input must contain only letters and spaces.\n");
        return false;
    }
    if (input.length() < minLength || input.length() > maxLength)
    {
        printf("Input must be between %hhu and %hhu characters long.\n", minLength, maxLength);
        return false;
    }

    return true;
}

bool Validation::IsValid(std::string input)
{
    for (int i = 0; i < input.length(); i++)
    {
        if (!isalpha(input[i]) && !isspace(input[i]))
        {
            return false;
        }
    }

    return true;
}

uint_fast16_t Validation::GetValidPIN(std::string prompt)
{
    uint_fast16_t temp{};

    do
    {
        printf("%s (%hhu numbers): ", prompt.c_str(), Constants::PIN_LENGTH);
        if (scanf_s("%hu", &temp) != 1)
        {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
    } 
    while (!ValidateNums(temp, Constants::PIN_LENGTH));

    return temp;
}

uint_fast16_t Validation::GetValidSCV(std::string prompt)
{
    uint_fast16_t temp{};

    do
    {
        printf("%s (%hhu numbers): ", prompt.c_str(), Constants::SCV_LENGTH);
        if (scanf_s("%hu", &temp) != 1)
        {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
    }
    while (!ValidateNums(temp, Constants::SCV_LENGTH));

    return temp;
}

bool Validation::ValidateNums(uint_fast16_t num, uint_fast8_t length)
{
    uint_fast8_t count = 0;

    if (num == 0)
    {
        count = 1;
    }
    while (num > 0)
    {
        num /= 10;
        count++;
    }

    if (count != length)
    {
        printf("Input must be exactly %hhu digits long.\n", length);
        return false;
    }

    return true;
}