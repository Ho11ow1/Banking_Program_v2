#ifndef CARD_H
#define CARD_H

#include <cstdio>
#include <cstdint>
#include <cstring>

#include "constants.h"

class Card
{
public:
    Card() noexcept = default;
    ~Card() noexcept = default;

    void Show_Card_Details() const noexcept;

private:
    char Card_number[Constants::CARD_NUMBER_SIZE]{};
    char Owner_name[Constants::NAME_SIZE]{};
    char Owner_Surname[Constants::NAME_SIZE]{};

    uint_fast16_t m_PIN{};
    uint_fast16_t m_SCV{};

    friend class Account;
};

#endif