#include <stdio.h>
#include <vector>

#include "./src/card.h"
#include "./src/account.h"

class Banking
{
public:
    void Run()
    {
        acc.Run();
    }

private:
    Account acc;
    std::vector<std::unique_ptr<Card>> cards;
};

int main()
{
    Banking bank;
    bank.Run();

    return 0;
}