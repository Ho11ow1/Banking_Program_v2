#pragma once

#include <memory>
#include <string>

class Card
{
public:
	Card() : Card_Number(GenNumber()), Card_Balance(0) {};

	std::string GetCardNumber() const { return Card_Number; };

private:
	std::string GenNumber();

	std::string Card_Number;
	uint64_t Card_Balance;

private:
	uint64_t m_MIN = 0000000000000001;
	uint64_t m_MAX = 999999999999999;
};