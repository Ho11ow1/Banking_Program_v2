#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <memory>

#include "./card.h"

class Banking
{
public:
    void Run()
    {
        cards.push_back(std::make_unique<Card>());

        printf("%s %s", "Card number: ", cards[0]->GetCardNumber().c_str());
    }

public:
    std::vector<std::unique_ptr<Card> > cards;
};

#endif