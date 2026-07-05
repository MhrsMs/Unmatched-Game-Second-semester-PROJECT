#ifndef DRWATSON_H
#define DRWATSON_H
#include "Hero.h"

class DrWatson: public Hero
{
public:
    DrWatson();
    void ability() override;
};


#endif