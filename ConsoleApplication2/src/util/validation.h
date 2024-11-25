#pragma once
#include <cstdint>

class Validation
{
public:
    char* ValidateInput(const char* input, size_t buffer);
private:
    char* GetValidInput(const char* input, uint_fast8_t minLength, uint_fast8_t maxLength);
    bool IsValid(const char* input);
};
