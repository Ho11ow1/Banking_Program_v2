#include <cstdio>
#include <random>

#include "./account.h"
#include "./card.h"
#include "./util/validation.h"
Validation validation;

bool Account::Register()
{
    accountNumber = GenerateNumber(); // Can change this into SQLite AUTOINCREMENT or leave as a creative decision
    accountHolder = validation.GetValidInput("Input accountHolder name");
    routingNumber = GenerateNumber(); // Can change this into SQLite AUTOINCREMENT or leave as a creative decision

    // Save all this to SQLite
    return true;
}

bool Account::Login()
{
    // TODO: Implement Login

    return true;
}

void Account::ShowDetails(Account &account, Card &card)
{
    printf("Account Number: %lld\n", account.accountNumber);
    printf("Account Holder: %s\n", account.accountHolder.c_str());
    printf("Routing Number: %lld\n", account.routingNumber);
    
    if (&card != nullptr)
    {
        printf("Card Details:\n");
        printf("  PIN: %d\n", card.PIN);
        printf("  SCV: %d\n", card.SCV);
        printf("  Balance: $%.2f\n", card.balance);
    }
}

uint_fast64_t Account::GenerateNumber() // Creative Decisions
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint_fast64_t> dis(0ULL, Constants::MAX_CARD_NUMBER);

    return dis(gen);
}
