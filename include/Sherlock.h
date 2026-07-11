#ifndef SHERLOCK_H
#define SHERLOCK_H
#include "Hero.h"

class Sherlock : public Hero
{
public:
    Sherlock(std::string short_name);
    void ability(Hero& hero, vector <Hero*> heros, CardManager& card) override;
};


#endif