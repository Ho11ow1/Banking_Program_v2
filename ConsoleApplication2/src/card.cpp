#include "./card.h"
#include <random>
#include <sstream>
#include <type_traits>

std::string Card::GenNumber()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<uint64_t> number(m_MIN, m_MAX); // distribution in range [1, 6]

	std::stringstream ss;
	ss << number(eng);
	return ss.str();
}