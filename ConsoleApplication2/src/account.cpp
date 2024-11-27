#include <cstdio>
#include <random>

#include "./account.h"
#include "./util/validation.h"
#include "util/generation.h"
Validation validation;

bool Account::Register()
{
    try
    {
        accountHolder = validation.GetValidInput("Input Account Name + Surname");
        accountNumber = GenerateNumber(); // leave as a creative decision
        routingNumber = GenerateNumber(); // leave as a creative decision
        accountBalance = 0;

        card.SetDetails();
        card.UpdateBalance(accountBalance);
    }
    catch (std::exception& e)
    {
        printf("%s", e.what());
        return false;
    }

    return true;
}

bool Account::Login()
{
    uint_fast64_t tempNumber{};
    std::string tempAccountHolder{};
    uint_fast64_t tempRouting{};

    // TODO: Implement Login

    if (tempNumber == accountNumber && tempAccountHolder == accountHolder && tempRouting == routingNumber)
    {
        return true;
    }

    return false;
}

void Account::ShowDetails() noexcept
{
    printf("Account Holder: %s", accountHolder.c_str());
    printf("Account Number: %lld\n", accountNumber);
    printf("Routing Number: %lld\n", routingNumber);
    printf("Account Balance: $%.2f\n", accountBalance);
    
    if (&card != nullptr)
    {
        printf("Card Details:\n");
        printf("  Card Number: %lld\n", card.GetCardNumber());
        printf("  PIN: %hu\n", card.GetPIN());
        printf("  SCV: %hu\n", card.GetSCV());
        printf("  Balance: $%.2f\n", card.GetBalance());
    }
}

void Account::UpdateBalance() noexcept
{
    int temp{};

    printf("Input Amount to Deposit: ");
    if (scanf_s("%d", &temp) != 1)
    {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (temp <= 0)
    {
        printf("Amount must be greater than 0\n");
        return;
    }

    accountBalance += temp;
    card.UpdateBalance(temp);
}
