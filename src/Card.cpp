#include "Card.h"

Card::Card(int id, string card_name, int attack_or_defense, string name_of_doer, int effect_time, int boost, int number, string kind_of_action, Needs needs) : id(id), card_name(card_name), attack_or_defense(attack_or_defense), name_of_doer(name_of_doer),
effect_time(effect_time), boost(boost), number(number), kind_of_action(kind_of_action), needs(needs)
{
}

int Card::get_id() const
{
    return id;
}

string Card::get_cardName() const
{
    return card_name;
}

int Card::get_attackOrDefense() const
{
    return attack_or_defense;
}

string Card::get_nameOfDoer() const
{
    return name_of_doer;
}

int Card::get_effectTime() const
{
    return effect_time;
}

int Card::get_boost() const
{
    return boost;
}

int Card::get_number() const
{
    return number;
}

string Card::get_kindOfAction() const
{
    return kind_of_action;
}

Needs Card::get_Needs() const
{
    return needs;
}

void Card::change_attackOrDefense(int num)
{
    attack_or_defense = +num;
}
