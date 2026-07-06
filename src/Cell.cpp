#include "Cell.h"
using namespace std;

Cell::Cell(int n, std::vector<std::string>& col, std::vector<int>& con, bool isp):
    number(n), color(col), connections(con), is_passage(isp){
        hero_inside= nullptr;
    }

int Cell::get_number() const
{
    return number;
}
std::vector<int> Cell::get_connections() const
{
    return connections;
}
std::vector<std::string> Cell::get_color() const
{
    return color;
}
bool Cell::Is_Passage() const
{
    return is_passage;
}
Hero* Cell::get_hero_inside() const
{
    return hero_inside;
}
void Cell::change_hero_inside(Hero* current_hero_inside)
{
    hero_inside= current_hero_inside;
}