#pragma once

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "./constants.h"

class Card;  // Forward declaration

class Account
{
public:
    Account() = default;

    bool Register();
    bool Login();
    void ShowDetails(Account &account, Card &card);

private:
    uint_fast64_t GenerateNumber();

private:
    uint_fast64_t accountNumber{};
    std::string accountHolder{};
    uint_fast64_t routingNumber{};
};

#endif