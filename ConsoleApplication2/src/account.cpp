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

        card.SetDetails();
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

void Account::ShowDetails(Account &account, Card &card) noexcept
{
    printf("Account Holder: %s", account.accountHolder.c_str()); // I gues c_str() adds a '\n' at the end
    printf("Account Number: %lld\n", account.accountNumber);
    printf("Routing Number: %lld\n", account.routingNumber);
    printf("Account Balance: %d\n", account.accountBalance);
    
    if (&card != nullptr)
    {
        printf("Card Details:\n");
        printf("  Card Number: %lld\n", card.GetCardNumber());
        printf("  PIN: %d\n", card.GetPIN());
        printf("  SCV: %d\n", card.GetSCV());
        printf("  Balance: $%.2f\n", card.GetBalance());
    }
}
