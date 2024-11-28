#ifndef CARD_H
#define CARD_H

#include <cstdint>

class Card
{
public:
    Card() = default;

    void SetDetails();
    uint_fast64_t GetCardNumber() const;
    uint_fast16_t GetPIN() const;
    uint_fast16_t GetSCV() const;
    double GetBalance() const;
    uint_fast64_t GetAccountNumber() const;
    void UpdateBalance(double amount) noexcept;
    
private:
    uint_fast64_t cardNumber{};
    uint_fast16_t PIN{};
    uint_fast16_t SCV{};
    double balance{};
};

#endif