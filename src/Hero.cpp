#include "Hero.h"
using namespace std;

Hero::Hero(string n, int hp, int m, string aT):
name(n), originalHP(hp), HP(hp), move(m), attackType(aT)
{
    position= 0;
}
string Hero::get_name() const
{
    return name;
}
int Hero::get_originalHP() const
{
    return originalHP;
}
int Hero::get_HP() const
{
    return HP;
}
int Hero::get_move() const
{
    return move;
}
string Hero::get_attackType() const
{
    return attackType;
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
        HP= 0;
    else
        HP-= damage;
}
void Hero::increase_HP(int heal)
{
    if((HP + heal)>=originalHP)
        HP= originalHP;
    else
        HP+= heal;
}
bool Hero::is_alive() const
{
    if(HP>0)
        return true;
    return false;
}