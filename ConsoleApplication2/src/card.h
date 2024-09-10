#ifndef CARD_H
#define CARD_H

#include <string>

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
    uint64_t m_MIN = 0000000000000001;
    uint64_t m_MAX = 999999999999999;

private:
    std::string GenNumber();
    void DB_Create();
    std::string B2 = "2B.txt";
};

#endif