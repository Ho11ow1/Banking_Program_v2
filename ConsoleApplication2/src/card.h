#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>

class Card
{
public:
	void Run()
	{
		Set_Card_Details();
	}

	void Show_Card_Details();

private:
	uint_fast64_t Gen_Card_Number();
	void Set_Card_Details();

	std::string Transfer_Card_Number();

	struct CARD
	{
		char Card_number[20];
		// Seperation
		char Owner_name[25];
		char Owner_Surname[25];

		uint_fast16_t m_PIN;
		uint_fast16_t m_SCV;
	} card;
};

#endif