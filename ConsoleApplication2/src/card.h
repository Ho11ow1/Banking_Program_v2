#ifndef CARD_H
#define CARD_H

#include <cstdint>

class Card
{
public:
    Card() = default;

    void SetDetails();
    uint_fast64_t GetCardNumber() const;
    uint_fast8_t GetPIN() const;
    uint_fast8_t GetSCV() const;
    double GetBalance() const;

private:
    uint_fast64_t cardNumber{};
    uint_fast8_t PIN{};
    uint_fast8_t SCV{};
    double balance{};
};

#endif