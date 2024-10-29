#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>
#include <cstddef>

namespace Constants 
{
    inline constexpr uint_fast8_t MAX_DB_NAME = 24;
    inline constexpr uint_fast8_t MAX_NAME_LENGTH = 24;
    inline constexpr uint_fast8_t MIN_NAME_LENGTH = 3;
    inline constexpr size_t CARD_NUMBER_SIZE = 20;
    inline constexpr size_t NAME_SIZE = 25;
}

#endif 