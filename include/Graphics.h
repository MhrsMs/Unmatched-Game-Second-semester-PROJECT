#pragma once
#include "ActionMenu.h"
#include "FirstMenu.h"
#include "InputMenu.h"
class Graphics
{
public:
	Graphics();
	int get_card(int a, int cards);
	void end_game(int a);
	int movement1(int a, std::vector <ActionMenu::cell>& current_cell, std::string name, int move);
	int ability();
	void text(int a, std::string t = "");
	int get_number();
	int get_hero(int a, const std::vector <std::string>& heros);
	void combat(int a, int damage);
	int run_first();
	std::vector <int> run_age();
	std::vector <int> run_legend(int a);
	int maneuver();
	int run_action();
	int help();
	int get_card_target(const std::vector <std::string>& hand);
	int get_card_action(const std::vector <std::string>& cards);
	void show_hand(const std::vector <std::string>& hand);
	bool is_new_click();
	int yes_or_no(int a);
	int get_foggy_cell(std::vector <int> cells);

private:
	void is_in_action();
	InputMenu input;
	FirstMenu first;
	bool click = 0;
public:
	ActionMenu action_menu;;
	std::vector <ActionMenu::cell> map;
	int turn = 0;
};

