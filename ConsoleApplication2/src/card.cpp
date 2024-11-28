#include "./card.h"
#include "./util/generation.h"
#include "./util/validation.h"

// Most likely to be empty as Card is just a data structure
// I guess that statement didn't last long

void Card::SetDetails()
{
	Validation validation;

	cardNumber = GenerateNumber();
	PIN = validation.GetValidPIN("Input Desired PIN");
	SCV = validation.GetValidSCV("Input Desired SCV");
}

uint_fast64_t Card::GetCardNumber() const
{
	return cardNumber;
}

uint_fast16_t Card::GetPIN() const
{
	return PIN;
}

uint_fast16_t Card::GetSCV() const
{
	return SCV;
}

double Card::GetBalance() const
{
	return balance;
}

uint_fast64_t Card::GetAccountNumber() const
{
	return 1;
}

void Card::UpdateBalance(double amount) noexcept // Refactor into a template from Account.ManageBalance()
{
	balance += amount;
}

