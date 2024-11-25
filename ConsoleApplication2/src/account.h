#pragma once

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "./constants.h"

class Card;  // Forward declaration

class Account
{
public:
    bool Register();
    bool Login();
    void ShowDetails(Account &account, Card &card);

private:
    uint_fast64_t GenerateNumber();

private:
    uint_fast64_t accountNumber;
    char accountHolder[Constants::MAX_NAME_LENGTH];
    uint_fast64_t routingNumber;
};

#endif