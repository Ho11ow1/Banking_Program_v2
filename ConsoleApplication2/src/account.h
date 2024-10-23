#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <memory>
#include <random>

class Card;

class Account
{
public:
    Account() : card(nullptr) {} // Initialize card to nullptr
    ~Account() {}   // Destructor to free memory

    void Run()
    {
        Create_Account();
        Set_Card_Details();
        Show_Card_Details();
    }

    void Create_Account();
    void Show_Card_Details();

private:
    uint_fast64_t Gen_Card_Number();
    void Set_Card_Details();
    std::string Transfer_Card_Number();
    //Seperation for checks
    bool ValidateInput(char(&input)[25], uint_fast8_t maxLength, uint_fast8_t minLength);
    bool ValidateNums(uint_fast16_t& input, uint_fast16_t MaxSize, uint_fast16_t MinSize);
    //Seperation for PIN / SCV checks. Not as simple as it seems, the user can be very dumb, Give me more Xanax and Benadryl
    uint_fast16_t Set_Pin(); // ToDo: Finish and check for digits

private:
    uint_fast8_t Account_ID{};
    Card* card;
};

#endif
