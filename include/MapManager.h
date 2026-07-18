#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include "Cell.h"
#include "Hero.h"

class MapManager
{
private:
    std::vector<Cell> cell;
public:
    MapManager();
    bool is_adjacent(int current_position, int chosen_cell) const;
    bool is_same_zone(int current_position, int chosen_cell) const;
    bool is_enemy_inside(int chosen_cell, Hero* current_hero);
    bool is_ally_inside(int chosen_cell, Hero* current_hero);
    std::vector<int> electable_cells(int current_position);
    std::vector<Hero*> nearby_heroes(int current_position);
    std::vector<std::string> text_inside_cells() const;
    void move(int chosen_cell, Hero* current_hero);
};

#endif