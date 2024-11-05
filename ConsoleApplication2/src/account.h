#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <memory>
#include <random>
#include <stdexcept>
#include <chrono>
#include <ctime>

#include "constants.h"
#include "card.h"
#include "balance.h"

class Account
{
public:
    Account() noexcept = default;
    ~Account() noexcept = default;

    void Run() noexcept;
    void fn_Create_Account();
    void fn_Show_Card_Details() const;
    //=============== BALANCE ===============
    bool Deposit(double amount) noexcept;
    bool Withdraw(double amount) noexcept;
    double Get_Balance() const noexcept;

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
    //=============== DB ===============
    void fn_Save_To_DB() const;

private:
    char DB[Constants::MAX_DB_NAME]{"2B.txt"};
    uint_fast64_t Account_ID{};
    std::unique_ptr<Card> card{};
    Balance balance{};
};

#endif

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <memory>
#include <string>
#include <cstdint>

#include "constants.h"
#include "card.h"
#include "balance.h"

class Account
{
public:
    Account() noexcept = default;
    ~Account() noexcept = default;

    void Run() noexcept;
    void fn_Create_Account();
    bool fn_Login();
    void fn_Show_Card_Details();
    //=============== BALANCE ===============
    bool Deposit(double amount) noexcept;
    bool Withdraw(double amount) noexcept;
    double Get_Balance() const noexcept;

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
    //=============== DB ===============
    void fn_Save_To_DB() const;

private:
    char DB[Constants::MAX_DB_NAME]{"2B.txt"};
    uint_fast64_t Account_ID{};
    std::unique_ptr<Card> card{};
    Balance balance{};
};

#endif
