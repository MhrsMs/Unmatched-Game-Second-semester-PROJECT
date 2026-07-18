#include "MapManager.h"
using namespace std;

MapManager::MapManager()
{
    ReadInformation rdi;
    cell= rdi.get_cell();
}
bool MapManager::is_adjacent(int current_position, int chosen_cell) const
{
    vector<int> current_connections= cell[current_position].get_connections();
    for(size_t i=0; i<current_connections.size(); i++)
    {
        if(current_connections[i]==chosen_cell)
            return true;
    }
    return false;
}
bool MapManager::is_same_zone(int current_position, int chosen_cell) const
{
    vector<string> current_zone= cell[current_position].get_color();
    vector<string> chosen_zone= cell[chosen_cell].get_color();
    for(size_t i=0; i<chosen_zone.size(); i++)
    {
        for(size_t j=0; j<current_zone.size(); j++)
        {
            if(chosen_zone[i]==current_zone[j])
                return true;
        }
    }
    return false;
}
bool MapManager::is_enemy_inside(int chosen_cell, Hero* current_hero)
{
    Hero* hero_inside_this_cell= cell[chosen_cell].get_hero_inside();
    if(hero_inside_this_cell!=nullptr)
    {
        if(hero_inside_this_cell->is_alive())
        {
            if(hero_inside_this_cell->get_name()=="SHERLOCK" || hero_inside_this_cell->get_name()=="DR.WATSON")
            {
                if(current_hero->get_name()!="SHERLOCK" && current_hero->get_name()!="DR.WATSON")
                    return true;
                else    
                    return false;
            }

            if(hero_inside_this_cell->get_name()=="DRACULA" || hero_inside_this_cell->get_name()=="SISTER")
            {
                if(current_hero->get_name()!="DRACULA" && current_hero->get_name()!="SISTER")
                    return true;
                else    
                    return false;
            }
        }
        else
        {
            cell[chosen_cell].change_hero_inside(nullptr);
            return false;
        }
    }
    else
    {
        return false;
    }

    return false;
}
bool MapManager::is_ally_inside(int chosen_cell, Hero* current_hero)
{
    Hero* hero_inside_this_cell= cell[chosen_cell].get_hero_inside();
    if(hero_inside_this_cell!=nullptr)
    {
        if(hero_inside_this_cell->is_alive())
        {
            if(hero_inside_this_cell->get_name()=="SHERLOCK" || hero_inside_this_cell->get_name()=="DR.WATSON")
            {
                if(current_hero->get_name()=="SHERLOCK" || current_hero->get_name()=="DR.WATSON")
                    return true;
                else    
                    return false;
            }

            if(hero_inside_this_cell->get_name()=="DRACULA" || hero_inside_this_cell->get_name()=="SISTER")
            {
                if(current_hero->get_name()=="DRACULA" || current_hero->get_name()=="SISTER")
                    return true;
                else    
                    return false;
            }
        }
        else
        {
            cell[chosen_cell].change_hero_inside(nullptr);
            return false;
        }
    }
    else
    {
        return false;
    }

    return false;
}
vector<int> MapManager::electable_cells(int current_position)
{
    vector<int> suitable_cells;
    vector<int> connections= cell[current_position].get_connections();
    Hero* current_hero= cell[current_position].get_hero_inside();
    for(size_t i=0; i<connections.size(); i++)
    {
        if(!(is_enemy_inside(connections[i], current_hero)))
            suitable_cells.push_back(connections[i]);
    }

    vector<int> passage= {1, 6, 16, 28};
    if(cell[current_position].Is_Passage())
    {
        for(size_t j=0; j<passage.size(); j++)
        {
            if(passage[j]==cell[current_position].get_number())
            {
                passage.erase(passage.begin()+j);
                break;
            }
        }

        for(size_t k=0; k<passage.size(); k++)
        {
            suitable_cells.push_back(passage[k]);
        }
    }

    return suitable_cells;
}
vector<Hero*> MapManager::nearby_heroes(int current_position)
{
    vector<Hero*> heroes_around;
    vector<int> connections= cell[current_position].get_connections();
    for(size_t i=0; i<connections.size(); i++)
    {
        Hero* hero =cell[connections[i]].get_hero_inside();
        if(hero != nullptr)
        {
            if(hero->is_alive())
            {
                heroes_around.push_back(hero);
            }
            else
            {
                cell[connections[i]].change_hero_inside(nullptr);
            }
        }
    }

    return heroes_around;
}
vector<string> MapManager::text_inside_cells() const
{
    vector<string> text;
    text.push_back("");
    for(size_t i=1; i<cell.size(); i++)
    {
        Hero* hero_inside= cell[i].get_hero_inside();
        if(hero_inside!=nullptr && hero_inside->get_position()!=0)
            text.push_back(hero_inside->get_short_name());
        else if(i<10)
            text.push_back("0"+ to_string(i));
        else
            text.push_back(to_string(i));
        
    }

    return text;
}
void MapManager::move(int chosen_cell, Hero* current_hero)
{
    int current_position= current_hero->get_position();
    if(current_position==0)
    {
        cell[chosen_cell].change_hero_inside(current_hero);
        current_hero->change_position(chosen_cell);
    }
    else
    {
        cell[chosen_cell].change_hero_inside(current_hero);
        current_hero->change_position(chosen_cell);
        cell[current_position].change_hero_inside(nullptr);
    }
}