#ifndef CARDMANAGER_H
#define CARDMANAGER_H
#include "Card.h"
#include "ReadInformation.h"
#include <vector>
#include <iostream>

class Hero;

class CardManager
{
public:
    std::vector<Card> deck;
    std::vector<Card> hand;
    std::vector<Card> null_card;

    CardManager(int a);
    void Shuffle(std::vector<Card>& set);
    bool can_deck_to_hand(int number);
    void deck_to_hand(int number);
    void hand_to_null_card(int id);
    std::vector<Card> get_cards_by_action(int action_type, Hero* doer_hero= nullptr);
};

#endif