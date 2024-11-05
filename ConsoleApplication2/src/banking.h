#ifndef BANKING_H
#define BANKING_H

#include "account.h"
#include <cstdio>

class Banking
{
public:
    Banking() = default;
    ~Banking() noexcept = default;
    
    void Run() noexcept;

private:
    Account acc{};
    //=============== VARIABLES ===============
    bool running = true;

    int choice{};
    double amount = 0.0;
};

#endif 