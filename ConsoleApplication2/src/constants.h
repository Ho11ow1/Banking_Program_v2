#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>
#include <cstddef>

namespace Constants 
{
    inline constexpr uint_fast8_t MAX_NAME_LENGTH = 24;
    inline constexpr uint_fast8_t MIN_NAME_LENGTH = 3;

    inline constexpr uint_fast8_t PIN_LENGTH = 4;
    inline constexpr uint_fast8_t SCV_LENGTH = 3;
    
    inline constexpr uint_fast8_t CARD_NUMBER_LENGTH = 20;
    inline constexpr uint_fast64_t MAX_CARD_NUMBER = 9999999999999999;

    inline constexpr char DB_NAME[6] = "2B.db";
}

#endif 