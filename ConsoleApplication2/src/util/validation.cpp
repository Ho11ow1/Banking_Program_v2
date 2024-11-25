#include <cstring>

#include "./validation.h"
#include "../constants.h"

char* Validation::ValidateInput(const char* input, size_t buffer)
{
    return GetValidInput(input, Constants::MIN_NAME_LENGTH, Constants::MAX_NAME_LENGTH);
}


char* Validation::GetValidInput(const char* input, uint_fast8_t minLength, uint_fast8_t maxLength)
{
    if (input == nullptr)
    {
        return nullptr;
    }
    if (strlen(input) < minLength || strlen(input) > maxLength)
    {
        return nullptr;
    }

    return (char*)input;
}

bool Validation::IsValid(const char* input)
{
    return true;
}