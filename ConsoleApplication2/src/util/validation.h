#pragma once

#include <cstdio>
#include <string>
#include "../constants.h"

class Validation
{
public:
    std::string GetValidInput(std::string prompt);
    uint_fast16_t GetValidPIN(std::string prompt);
    uint_fast16_t GetValidSCV(std::string prompt);
private:
    bool ValidateInput(std::string input, uint_fast8_t minLength, uint_fast8_t maxLength);
    bool ValidateNums(uint_fast16_t num, uint_fast8_t length);
    bool IsValid(std::string input);
};
