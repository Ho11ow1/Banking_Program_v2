#include "./card.h"

std::string Card::GenNumber()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<uint64_t> number(m_MIN, m_MAX);

	DB_Create();

	uint64_t randomNumber = number(eng);
	return std::to_string(randomNumber);
}

void Card::DB_Create() // works with string in function | doesn't work with string in declaration
{
	const std::string m_DB = "2B.txt";
	std::ofstream file(m_DB, std::ios::out | std::ios::app);

	if (!file)
	{
		return;
	}

	file << "I'm going to kill myself\n";

	file.close();
}