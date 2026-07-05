#ifndef SHERLOCK_H
#define SHERLOCK_H
#include "Hero.h"

class Sherlock: public Hero
{
public:
    Sherlock();
    void ability() override;
};


#endif