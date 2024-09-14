#ifndef CARD_H
#define CARD_H

#include <string>
#include <random>
#include <fstream>
#include <filesystem>

class Card 
{
public:
    Card() : Card_Number(GenNumber()), Card_Balance(0) {};

    Card(Card&& old) noexcept :
        Card_Number(std::move(old.Card_Number)),
        Card_Balance(std::move(old.Card_Balance)) {}

    std::string GetCardNumber() const { return Card_Number; };

public:
    std::string Card_Number;
    uint64_t Card_Balance;

private:
    const uint64_t m_MIN = 1000000000000000;
    const uint64_t m_MAX = 9999999999999999;

private:
    std::string GenNumber(); 
    void DB_Create(); // string length error hell
};

#endif