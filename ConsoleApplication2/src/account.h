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
    void ShowDetails() noexcept;
    void UpdateBalance() noexcept;

    std::string GetaccountHolder() const;
    uint_fast64_t GetAccoutNumber() const;
    uint_fast64_t GetAccoutRoutingNumber() const;
    double GetAccountBalance() const;
    void GetBalance() const;
private:
    Card card;

    std::string accountHolder{};
    uint_fast64_t accountNumber{};
    uint_fast64_t routingNumber{};
    double accountBalance = 0;
};

#endif