#include "./generation.h"

uint_fast64_t GenerateNumber() // Creative Decisions
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint_fast64_t> dis(0ULL, Constants::MAX_CARD_NUMBER);

    return dis(gen);
}