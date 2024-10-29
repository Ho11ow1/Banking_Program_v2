#include <cstdio>
#include <exception>

#include "./src/account.h"

class Banking
{
public:
    Banking() = default;
    ~Banking() noexcept = default;
    
    void Run() noexcept 
    {
        acc.Run();
    }

private:
    Account acc{};
};

int main()
{
    try 
    {
        Banking bank;
        bank.Run();
        return 0;
    }
    catch (const std::exception& e) 
    {
        printf("Fatal error: %s\n", e.what());
        return 1;
    }
}