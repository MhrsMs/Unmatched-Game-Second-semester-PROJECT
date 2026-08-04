#ifndef INVISIBLEMAN_H
#define INVISIBLEMAN_H
#include "Hero.h"

class InvisibleMan : public Hero
{
public:
    InvisibleMan(std::string short_name);
    void ability(Hero& hero, vector <Hero*> heros, CardManager& card) override;
};


#endif