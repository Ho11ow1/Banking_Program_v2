#include "./src/card.h"

class Banking
{
public:
    void Run() const
    {
        printf("%s, %s", "Card number: ", card->GetCardNumber());
    }

private:
    std::unique_ptr<Card> card = std::make_unique<Card>();
};

int main()
{

    Banking bank;
    bank.Run();

    return 0;
}