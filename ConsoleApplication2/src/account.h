#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <memory>
#include <random>
#include <stdexcept>

#include "constants.h"
#include "card.h"

class Card;

class Account
{
public:
    Account() noexcept = default;
    //Account() noexcept : Account_ID{0}, card{nullptr}{}; // Add back when balance implementation is introduced
    ~Account() noexcept = default;

    void Run() noexcept;
    void fn_Create_Account();
    void fn_Show_Card_Details() const;

private:
    uint_fast64_t fn_Gen_Card_Number();
    std::string fn_Transfer_Card_Number();
    //=============== SETTERS ===============
    void fn_Set_Card_Details();
    uint_fast16_t fn_Set_Pin();
    void fn_set_Card_Names(char(&destination)[Constants::NAME_SIZE], const char* prompt) noexcept;
    //=============== VALIDATION ===============
    bool fn_ValidateInput(char(&input)[Constants::NAME_SIZE], uint_fast8_t maxLength, uint_fast8_t minLength) const;
    bool fn_ValidateNums(uint_fast16_t& input, uint_fast16_t MaxSize, uint_fast16_t MinSize) const;
    bool fn_DB_Exist(const char(&DB_NAME)[Constants::MAX_DB_NAME]) const;

private:
    char DB[Constants::MAX_DB_NAME]{"2B.txt"};
    uint_fast8_t Account_ID{};
    std::unique_ptr<Card> card{};
};

#endif
