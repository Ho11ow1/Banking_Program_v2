#include "./card.h"

#include <random>
#include <fstream>

std::string Card::GenNumber()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<uint64_t> number(m_MIN, m_MAX);

	//DB_Create();

	uint64_t randomNumber = number(eng);
	return std::to_string(randomNumber);
}
/*
void Card::DB_Create()
{
	std::fstream file;
	file.open(B2, std::fstream::in | std::fstream::out | std::fstream::app);    // I'm gonna kill myself <3 :3

	file << "Help!";

	file.close();


}
*/