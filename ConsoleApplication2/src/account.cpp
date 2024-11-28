#include <cstdio>
#include <random>

#include "./account.h"
#include "./database.h"
#include "./util/validation.h"
#include "./util/generation.h"
Database DB;
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

        DB.SaveAccount(*this);
        DB.SaveCard(card);
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
        return true; // Call from records
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

void Account::UpdateBalance() noexcept // Turn this into a helper function to handle both withdraw and deposit
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

std::string Account::GetaccountHolder() const
{
    return accountHolder;
}

uint_fast64_t Account::GetAccoutNumber() const
{
    return accountNumber;
}

uint_fast64_t Account::GetAccoutRoutingNumber() const
{
    return routingNumber;
}

double Account::GetAccountBalance() const
{
    return accountBalance;
}

void Account::GetBalance() const
{
    printf("Account Balance: %.2lf", accountBalance);
}