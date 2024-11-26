#include <cstdio>
#include <cstring>
#include <random>

#include "./account.h"
#include "./card.h"
#include "./util/validation.h"
Validation validation;

bool Account::Register()
{
    accountNumber = GenerateNumber(); // Can change this into SQLite AUTOINCREMENT or leave as a creative decision
    strcpy_s(accountHolder, sizeof(accountHolder), validation.ValidateInput(accountHolder, sizeof(accountHolder)));
    routingNumber = GenerateNumber(); // Can change this into SQLite AUTOINCREMENT or leave as a creative decision
accountBalance = init with 0; // Set same on card as a ref for ease of use


    return true;
}

bool Account::Login()
{
unit tempnumber;
string tempaccountholder;
uint temp routing;

if temp == Get from DB { true; }
    // TODO: Implement Login

    return true;
}

void Account::ShowDetails(Account &account, Card &card)
{
    printf("Account Number: %lld\n", account.accountNumber);
    if (&card != nullptr)
    {
        printf("PIN: %d\n", card.PIN);
        printf("SCV: %d\n", card.SCV);
        printf("Balance: %.2f\n", card.balance);
    }
    printf("Account Holder: %s\n", account.accountHolder);
    printf("Routing Number: %lld\n", account.routingNumber);
}

uint_fast64_t Account::GenerateNumber()
{
    uint_fast64_t num{};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, Constants::MAX_CARD_NUMBER);

    return (uint_fast64_t)dis(gen);
}
