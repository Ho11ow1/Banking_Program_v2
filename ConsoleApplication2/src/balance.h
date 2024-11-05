#ifndef BALANCE_H
#define BALANCE_H

#include <cstdint>
#include <cstdio>

class Balance 
{
public:
    Balance() noexcept = default;
    ~Balance() noexcept = default;

    bool Withdraw(double amount, uint_fast64_t account_id) noexcept;
    bool Deposit(double amount, uint_fast64_t account_id) noexcept;
    double Get_Balance(uint_fast64_t account_id) const noexcept;

    double GetCurrentBalance() const noexcept { return m_Balance; }

private:
    double m_Balance{0.0};
    uint_fast64_t m_Account_ID{};

    static constexpr double MAX_TRANSACTION = 1000000.0;

    bool ValidateAmount(double amount) const noexcept
    {
        return amount > 0.0 && amount <= MAX_TRANSACTION;
    }
};

#endif
