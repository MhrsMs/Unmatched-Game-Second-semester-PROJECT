#include "Hero.h"
using namespace std;

Hero::Hero(string sn, string n, int hp, int m, string aT):
short_name(sn), name(n), original_HP(hp), HP(hp), move(m), attack_type(aT)
{
    position= 0;
}
string Hero::get_name() const
{
    return name;
}
string Hero::get_short_name() const
{
    return short_name;
}
int Hero::get_original_HP() const
{
    return original_HP;
}
int Hero::get_HP() const
{
    return HP;
}
int Hero::get_move() const
{
    return move;
}
string Hero::get_attack_type() const
{
    return attack_type;
}
int Hero::get_position() const
{
    return position;
}
void Hero::change_position(int currentPosition)
{
    position= currentPosition;
}
void Hero::decrease_HP(int damage)
{
    if(HP<=damage)
    {
        HP= 0;
        change_position(0);
    }
    else
        HP-= damage;
}
void Hero::increase_HP(int heal)
{
    if((HP + heal)>=original_HP)
        HP= original_HP;
    else
        HP+= heal;
}
bool Hero::is_alive() const
{
    if(HP>0)
        return true;
    return false;
}
void Hero::change_move(int m)
{
    move = move + m;
}