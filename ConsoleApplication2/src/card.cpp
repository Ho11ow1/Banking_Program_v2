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

	cardNumber = GenerateNumber();
	PIN = validation.GetValidPIN("Input Desired PIN");
	CSV = validation.GetValidCSV("Input Desired CSV");
	accountNumber = accountNum;

	Database DB;
	if (!DB.SaveCard(*this)) 
	{
		printf("Failed to save card details to database\n");
	}
}

void Card::UpdateBalance(double amount) noexcept
{
    // For withdrawals (negative amounts), check if sufficient funds exist
    if (amount < 0 && std::abs(amount) > balance) 
	{
        printf("Insufficient funds. Current balance: $%.2f\n", balance);
        return;
    }
    
    balance += amount;
    
    // Update the database
    Database DB;
    if (!DB.UpdateBalances(accountNumber, balance)) 
	{
        printf("Failed to update balances in database\n");
        return;
    }
    
    printf("Transaction successful. New balance: $%.2f\n", balance);
}
// Getters and Setters
uint_fast64_t Card::GetCardNumber() const
{
	return cardNumber;
}

uint_fast16_t Card::GetPIN() const
{
	return PIN;
}

uint_fast16_t Card::GetCSV() const
{
	return CSV;
}

double Card::GetBalance() const
{
	return balance;
}

uint_fast64_t Card::GetAccountNumber() const
{
	return accountNumber;
}

void Card::SetCardNumber(uint_fast64_t cardNum)
{
	cardNumber = cardNum;
}

void Card::SetPIN(uint_fast16_t pin)
{
	PIN = pin;
}

void Card::SetCSV(uint_fast16_t csv)
{
	CSV = csv;
}

void Card::SetBalance(double amount)
{
	balance = amount;
}
