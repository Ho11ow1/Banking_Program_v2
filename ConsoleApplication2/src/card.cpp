#include "card.h"

void Card::Show_Card_Details() const noexcept
{
    printf("\nCard_Owner_Name: %s\n", Owner_name);
    printf("Card_Owner_Surname: %s\n", Owner_Surname);
    printf("Card_number: %s\n", Card_number);
    printf("Card_PIN: %hu\n", m_PIN);
    printf("Card_SCV: %hu\n", m_SCV);
}