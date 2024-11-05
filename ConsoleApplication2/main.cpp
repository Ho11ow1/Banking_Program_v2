#include <cstdio>
#include <exception>

#include "./src/banking.h"

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