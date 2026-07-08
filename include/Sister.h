#ifndef SISTER_H
#define SISTER_H
#include "Hero.h"

class Sister: public Hero
{
public:
    Sister(std::string short_name);
    void ability() override;
};


#endif