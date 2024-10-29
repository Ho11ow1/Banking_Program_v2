#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>
#include <cstddef>

namespace Constants 
{
    inline constexpr size_t NAME_SIZE = 25;
    inline constexpr uint_fast8_t MAX_NAME_LENGTH = 24;
    inline constexpr uint_fast8_t MIN_NAME_LENGTH = 3;

    inline constexpr uint_fast16_t PIN_LENGTH = 4;
    inline constexpr uint_fast16_t SCV_LENGTH = 3;
    
    inline constexpr uint_fast16_t CARD_NUMBER_LENGTH = 20;
    inline constexpr uint_fast64_t MAX_CARD_NUMBER = 9999999999999999;

    inline constexpr uint_fast8_t MAX_DB_NAME = 24;
}

#endif 