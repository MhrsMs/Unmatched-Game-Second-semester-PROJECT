#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include "ActionMenu.h"
class InputMenu
{
public:
	void load_movement();
	void draw_movement(int a,std::vector <ActionMenu::cell> &map, std::string name, int move = 0);
	void unload_movement();
	int check_movement(std::vector <ActionMenu::cell>& map);
	void load_maneuver();
	void unload_maneuver();
	void draw_maneuver();
	int check_maneuver();
	void load_card();
	void draw_card(Texture2D &card);
	void unload_card();
	std::vector<Texture2D> load_hero(const std::vector<std::string>& hero);
	void unload_hero(std::vector <Texture2D>& hero);
	void draw_hero(int a,std::vector <Texture2D> &hero);
	int check_hero(int hero);
	int check_cards(int a, int cards);
	void draw_hand(std::vector <Texture2D> &cards);
	void load_combat();
	void unload_combat();
	void draw_combat(int damage, int a);
	void load_YN();
	void unload_YN();
	void draw_YN(int a);
	int check_YN(int a);
	void draw_text(std::string text);
	void draw_none();
	std::vector<Texture2D> load_hand(const std::vector<std::string>& hand);
	void unload_hand(std::vector<Texture2D> &hand);
	
private:
	Texture2D cell;
	Texture2D button;
	Texture2D divider;
	Texture2D attack;
	Texture2D defense;
	Font font = LoadFont("../Assets/font.ttf");
};