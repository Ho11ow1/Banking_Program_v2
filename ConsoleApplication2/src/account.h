#pragma once

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "./constants.h"
#include "./card.h"

class Account
{
public:
    Account() = default;

    bool Register();
    bool Login();
    void ShowDetails(Account& account, Card& card) noexcept;

private:
    Card card;

    std::string accountHolder{};
    uint_fast64_t accountNumber{};
    uint_fast64_t routingNumber{};
    uint_fast32_t accountBalance{0};
};

#endif