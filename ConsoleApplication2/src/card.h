#ifndef CARD_H
#define CARD_H

#include <string>
#include "./account.h"

class Card
{
public:
	void Show_Card_Details();

private:
	char Card_number[20];
		// Seperation
	char Owner_name[25];
	char Owner_Surname[25];

	uint_fast16_t m_PIN;
	uint_fast16_t m_SCV;

	friend class Account;
};

#endif