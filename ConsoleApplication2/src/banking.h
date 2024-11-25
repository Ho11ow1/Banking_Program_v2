#ifndef BANKING_H
#define BANKING_H

#include <cstdint>

#include "./account.h"
#include "./card.h"
class Banking
{
public:
    void Run() noexcept;

private:
    Account account{};
    Card card{};

    bool isLoggedIn{false};
    bool isRunning{true};
    uint_fast8_t choice;
};

#endif