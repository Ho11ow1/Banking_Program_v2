#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>

class Card
{
public:
	void Run()
	{
		Gen_Card_Number();
	}

	void Show_Card_Number();

public:
	uint_fast64_t Card_number{};
	// Seperation
	std::string Owner_name;
	std::string Owner_Surname;

private:
	void Gen_Card_Number();
	// Seperation
	uint8_t m_PIN{};
	uint8_t m_SCV{};
};

#endif