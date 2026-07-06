#include "CardManager.h"
#include "ReadInformation.h"
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

CardManager::CardManager(int a)
{
    ReadInformation rdi;
    deck= rdi.get_card(a);
    Shuffle(deck);
    deck_to_hand(5);
}
void CardManager::Shuffle(vector<Card>& set)
{
    random_device rd;
    mt19937 g(rd());
    shuffle(set.begin(), set.end(), g);
}
bool CardManager::can_deck_to_hand(int number)
{
    if(deck.size()>=number)
        return true;
    return false;
}
void CardManager::deck_to_hand(int number)
{
    for(size_t i=0; i<number; i++)
    {
        hand.push_back(deck.back());
        deck.pop_back();
    }
}
void CardManager::hand_to_null_card(int choice)
{
    null_card.push_back(hand[choice]);
    if(!(hand.empty()))
    {
        hand.erase(hand.begin()+choice);
    }
}
//void pair_card_with_effect()