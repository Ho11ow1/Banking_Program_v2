#pragma once

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "./card.h"

class Account
{
public:
    Account() = default;

    bool Register();
    bool Login();
    void ShowDetails() noexcept;
    void ManageBalance() noexcept;
    void UpdateBalance(double amount);

    // Getters
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

private:
    void HandleBalance(bool Deposit) noexcept;
};

#endif