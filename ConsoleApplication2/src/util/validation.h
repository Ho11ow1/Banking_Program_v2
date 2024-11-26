#pragma once

#include <cstdio>
#include <string>
#include "../constants.h"

class Validation
{
public:
    std::string GetValidInput(std::string prompt);
private:
    bool ValidateInput(std::string input, uint_fast8_t minLength, uint_fast8_t maxLength);
    bool IsValid(std::string input);
};
