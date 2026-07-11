#ifndef SISTER_H
#define SISTER_H
#include "Hero.h"

class Sister : public Hero
{
public:
    Sister(std::string short_name);
    void ability(Hero& hero, vector <Hero*> heros, CardManager& card) override;
};


#endif