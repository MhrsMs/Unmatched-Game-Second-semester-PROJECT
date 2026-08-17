#ifndef CELL_H
#define CELL_H
#include <vector>
#include <string>

class Hero;

class Cell
{
private:
    int number;
    std::vector<std::string> color;
    std::vector<int> connections;
    bool is_passage;
    Hero* hero_inside;
    bool fog;
    float x;
    float y;
public:
    Cell(int n, std::vector<std::string> col, std::vector<int> con, bool isp,float x,float y);
    int get_number() const;
    std::vector<std::string> get_color() const;
    std::vector<int> get_connections() const;
    bool Is_Passage() const;
    Hero* get_hero_inside() const;
    void change_hero_inside(Hero* current_hero_inside);
    bool get_fog() const;
    void change_fog(bool fogg);
    float get_x() const;
    float get_y() const;
};

#endif