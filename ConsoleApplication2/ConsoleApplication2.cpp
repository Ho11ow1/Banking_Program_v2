#include <stdio.h>
#include <vector>

#include "./src/card.h"

class Banking
{
public:
    void Run()
    {
        car.Run();
        car.Show_Card_Number();
    }

private:
    Card car;
    std::vector<std::unique_ptr<Card>> cards;
};

int main()
{
    Banking bank;
    bank.Run();

    return 0;
}