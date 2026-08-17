#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <string>
#include "CardManager.h"
class Hero
{
private:
    std::string name;
    const int original_HP;
    int HP;
    int original_move;
    int move;
    std::string attack_type;
    int position;
    std::string photo;
public:
    Hero(std::string ph, std::string n, int hp, int m, std::string aT);
    virtual ~Hero() = default;
    std::string get_name() const;
    std::string get_photo() const;
    int get_original_HP() const;
    int get_HP() const;
    int get_move() const;
    std::string get_attack_type() const;
    int get_position() const;
    void change_position(int currentPosition);
    void decrease_HP(int damage);
    void increase_HP(int heal);
    bool is_alive() const;
    virtual void ability(Hero& hero, vector <Hero*> heros, CardManager& card) = 0;
};



#endif