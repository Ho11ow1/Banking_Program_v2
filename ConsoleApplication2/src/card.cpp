#include <cstdio> // DEBUG
#include "./card.h"
#include "./database.h"
#include "./util/generation.h"
#include "./util/validation.h"

// Most likely to be empty as Card is just a data structure
// I guess that statement didn't last long

void Card::SetDetails(uint_fast64_t accountNum)
{
	Validation validation;

	m_cardNumber = GenerateNumber();
	m_PIN = validation.GetValidPIN("Input Desired PIN");
	m_CSV = validation.GetValidCSV("Input Desired CSV");
	m_accountNumber = accountNum;

	Database DB;
	if (!DB.SaveCard(*this)) 
	{
		printf("Failed to save card details to database\n");
	}
}

void Card::UpdateBalance(double amount) noexcept
{
    // For withdrawals (negative amounts), check if sufficient funds exist
    if (amount < 0 && std::abs(amount) > m_balance)
	{
        printf("Insufficient funds. Current balance: $%.2f\n", m_balance);
        return;
    }
    
	m_balance += amount;
    
    // Update the database
    Database DB;
    if (!DB.UpdateBalances(m_accountNumber, m_balance))
	{
        printf("Failed to update balances in database\n");
        return;
    }
    
    printf("Transaction successful. New balance: $%.2f\n", m_balance);
}
// Getters and Setters
uint_fast64_t Card::GetCardNumber() const
{
	return m_cardNumber;
}

uint_fast16_t Card::GetPIN() const
{
	return m_PIN;
}

uint_fast16_t Card::GetCSV() const
{
	return m_CSV;
}

double Card::GetBalance() const
{
	return m_balance;
}

uint_fast64_t Card::GetAccountNumber() const
{
	return m_accountNumber;
}

void Card::SetCardNumber(uint_fast64_t cardNum)
{
	m_cardNumber = cardNum;
}

void Card::SetPIN(uint_fast16_t pin)
{
	m_PIN = pin;
}

void Card::SetCSV(uint_fast16_t csv)
{
	m_CSV = csv;
}

void Card::SetBalance(double amount)
{
	m_balance = amount;
}
