#ifndef CELL_H
#define CELL_H
#include "Hero.h"
#include <vector>

class Cell
{
private:
    int number;
    std::vector<std::string> color;
    std::vector<int> connections;
    bool is_passage;
    Hero* hero_inside;
public:
    Cell(int n, std::vector<std::string> col, std::vector<int> con, bool isp);
    int get_number() const;
    std::vector<std::string> get_color() const;
    std::vector<int> get_connections() const;
    bool Is_Passage() const;
    Hero* get_hero_inside() const;
    void change_hero_inside(Hero* current_hero_inside);
};

#endif