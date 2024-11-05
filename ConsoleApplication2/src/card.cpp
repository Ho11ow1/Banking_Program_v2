#include <cstdio>
#include "card.h"

void Card::Show_Card_Details() const noexcept
{
    printf("\n=== Card Details ===\n");
    printf("Owner Name: %s\n", Owner_name);
    printf("Owner Surname: %s\n", Owner_Surname);
    printf("Card Number: %s\n", Card_number);
    printf("PIN: %hu\n", m_PIN);
    printf("SCV: %hu\n", m_SCV);
    printf("===================\n");
}