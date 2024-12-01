#pragma once

#include <string>
#include "../constants.h"

class Validation
{
public:
    std::string GetValidInput(std::string prompt);
    uint_fast16_t GetValidPIN(std::string prompt);
    uint_fast16_t GetValidCSV(std::string prompt);
    uint_fast64_t GetValid64(std::string prompt);
private:
    bool ValidateInput(std::string input, uint_fast8_t minLength, uint_fast8_t maxLength);
    bool IsValid(std::string input);
    template <typename T>
    bool ValidateNums(T num, uint_fast8_t length)
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
            printf("Input must be exactly %hhu digits long.\n", (uint_fast8_t)length);
            return false;
        }

        return true;
    }
};
