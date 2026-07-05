#ifndef DRACULA_H
#define DRACULA_H
#include "Hero.h"

class Dracula: public Hero
{
public:
    Dracula();
    void ability() override;
};


#endif