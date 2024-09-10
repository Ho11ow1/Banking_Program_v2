#include "./src/card.h"
#include <vector>

class Banking
{
public:
    void Run()
    {
        cards.push_back(Card());

        printf("%s %s", "Card number: ", cards[0].GetCardNumber().c_str());
        
    }

private:
    std::vector<Card> cards;
};

int main()
{
    Banking bank;
    bank.Run();

    return 0;
}