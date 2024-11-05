#include <cstdio>
#include <cstdlib>
#include "balance.h"

bool Balance::Withdraw(double amount, uint_fast64_t account_id) noexcept 
{
    if (!validateAccountId(account_id)) 
    {
        system("cls");
        printf("Invalid account ID\n");
        return false;
    }
    
    if (amount <= 0) {
        printf("%.2f is an invalid amount\n", amount);
        return false;
    }
    if (amount > m_Balance) 
    {
        printf("You do not have enough funds to withdraw %.2f\n", amount);
        return false;
    }
    
    m_Balance -= amount;

    return true;
}

bool Balance::Deposit(double amount, uint_fast64_t account_id) noexcept 
{
    if (!validateAccountId(account_id)) 
    {
        system("cls");
        printf("Invalid account ID\n");
        return false;
    }
    
    if (!ValidateAmount(amount)) {
        printf("%.2f is an invalid amount\n", amount);
        return false;
    }
    
    m_Balance += amount;

    return true;
}

double Balance::Get_Balance(uint_fast64_t account_id) const noexcept
{
    if (m_Account_ID != 0 && m_Account_ID != account_id)
    {
        printf("Invalid account ID\n");
        return 0.0;
    }

    printf("Your balance is: %.2f\n", m_Balance);

    return m_Balance;
}
