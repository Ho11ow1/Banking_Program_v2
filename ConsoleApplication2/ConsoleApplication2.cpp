#include "./src/card.h"
#include <vector>
#include <memory>

class Banking
{
public:
    void Run()
    {
        cards.push_back(std::make_unique<Card>());

        printf("%s %s", "Card number: ", cards[0] -> GetCardNumber().c_str());
        
    }

private:
    std::vector<std::unique_ptr<Card> > cards;
};

int main()
{
    Banking bank;
    bank.Run();

    return 0;
}