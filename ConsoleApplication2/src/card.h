#ifndef CARD_H
#define CARD_H

#include <cstdint>

class Card
{
public:
    Card() = default;

    void SetDetails(uint_fast64_t accountNum);
    void UpdateBalance(double amount) noexcept;
    // Getters
    uint_fast64_t GetCardNumber() const;
    uint_fast16_t GetPIN() const;
    uint_fast16_t GetCSV() const;
    double GetBalance() const;
    uint_fast64_t GetAccountNumber() const;
    // Setters
    void SetCardNumber(uint_fast64_t cardNum);
    void SetPIN(uint_fast16_t pin);
    void SetCSV(uint_fast16_t csv);
    void SetBalance(double amount);
    
private:
    uint_fast64_t cardNumber{};
    uint_fast16_t PIN{};
    uint_fast16_t CSV{};
    double balance{};
    uint_fast64_t accountNumber{};
};

#endif