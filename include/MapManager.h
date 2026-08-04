#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include "Cell.h"
#include "Hero.h"
#include "ReadInformation.h"

class MapManager
{
private:
    std::vector<Cell> cell;
public:
    MapManager();
    Cell* get_cell(int number);
    bool is_adjacent(int current_position, int chosen_cell) const;
    bool is_same_zone(int current_position, int chosen_cell) const;
    bool is_enemy_inside(int chosen_cell, Hero* current_hero);
    bool is_ally_inside(int chosen_cell, Hero* current_hero);
    std::vector<int> electable_cells(int current_position);
    std::vector<Hero*> nearby_heroes(int current_position);
    std::vector<std::string> text_inside_cells();
    void move(int chosen_cell, Hero* current_hero);
    bool is_foggy(int position) const;
    void set_foggy(int chosen_cell, int current_cell=0);
    std::vector<int> get_foggy_cells() const;
    std::vector<int> all_adjacent_cells(int position) const;
};

#endif