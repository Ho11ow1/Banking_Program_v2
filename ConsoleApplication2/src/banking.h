#ifndef BANKING_H
#define BANKING_H

#include "account.h"

class Banking
{
public:
    Banking() = default;
    ~Banking() noexcept = default;
    
    void Run() noexcept;

private:
    template<typename Func>
    void fn_Handle_Balance(const char* prompt, Func&& operation);

    Account acc{};
    //=============== VARIABLES ===============
    bool running = true;

    int choice{};
    double amount = 0.0;

    bool logged_in{false};
};

#endif 