#ifndef BANKING_H
#define BANKING_H

#include <cstdint>

#include "./account.h"
#include "./database.h"

class Banking
{
public:
    Banking() = default;

    void Run() noexcept;

private:
    Account account{};
    Database DB{};

    bool isLoggedIn{false};
    bool isRunning{true};
    uint_fast8_t choice{};
};

#endif