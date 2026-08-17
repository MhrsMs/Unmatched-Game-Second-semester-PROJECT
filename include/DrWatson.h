#ifndef DRWATSON_H
#define DRWATSON_H
#include "Hero.h"

class DrWatson : public Hero
{
public:
    DrWatson(std::string photo);
    void ability(Hero& hero, vector <Hero*> heros, CardManager& card) override;
};


#endif