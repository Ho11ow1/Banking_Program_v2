#include "./generation.h"
#include "../constants.h"

uint_fast64_t NumberGenerator::generateNumber() 
{
    std::uniform_int_distribution<uint_fast64_t> dis(0ULL, Constants::MAX_CARD_NUMBER);

    return dis(gen);
}