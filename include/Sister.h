#ifndef SISTER_H
#define SISTER_H
#include "Hero.h"

class Sister: public Hero
{
public:
    Sister();
    void ability() override;
};


#endif