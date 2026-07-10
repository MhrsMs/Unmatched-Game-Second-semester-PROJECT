#ifndef DRWATSON_H
#define DRWATSON_H
#include "Hero.h"

class DrWatson: public Hero
{
public:
    DrWatson(std::string short_name);
    void ability(Hero& hero) override;
};


#endif