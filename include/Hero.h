#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <string>

class Hero
{
private:
    std::string name;
    const int originalHP;
    int HP;
    int move;
    std::string attackType;
    int position;
public:
    Hero(std::string n, int hp, int m, std::string aT);
    std::string get_name() const;
    int get_originalHP() const;
    int get_HP() const;
    int get_move() const;
    std::string get_attackType() const;
    int get_position() const;
    void change_position(int currentPosition);
    void decrease_HP(int damage);
    void increase_HP(int heal);
    bool is_alive() const;
    virtual void ability()= 0;
};



#endif