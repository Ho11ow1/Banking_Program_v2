#ifndef BANKING_H
#define BANKING_H

#include <cstdint>

#include "./account.h"
#include "./card.h"
#include "./database.h"

class Banking
{
public:
    Banking()
    {
        account = Account();
        card = Card();
        DB = Database();
    };
    void Run() noexcept;

private:
    Account account{};
    Card card{};
    Database DB{};
    bool isLoggedIn{false};
    bool isRunning{true};
    uint_fast8_t choice;
};

#endif