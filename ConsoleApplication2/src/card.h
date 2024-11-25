#ifndef CARD_H
#define CARD_H

#include <cstdint>

class Card
{
public:
    uint_fast8_t PIN;
    uint_fast8_t SCV;
    double balance;

private:
    uint_fast64_t cardNumber;
};

#endif