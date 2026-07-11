#ifndef DRACULA_H
#define DRACULA_H
#include "Hero.h"

class Dracula : public Hero
{
public:
    Dracula(std::string short_name);
    void ability(Hero& hero, vector <Hero*> heros, CardManager& card) override;
};


#endif