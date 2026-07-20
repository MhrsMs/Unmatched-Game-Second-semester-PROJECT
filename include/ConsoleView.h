#pragma once
#include <vector>
#include <string>
using namespace std;
struct ShowActionMenu
{
	bool attack;
	bool scheme;
	string attackReason;
	string schemeReason;
	string name;
	vector <string> nameOfHero;
	vector <int> health;
	vector <int> move;
	vector <int> cell;
	vector <string> text;
	vector <string> card;
	vector <string> kind;
	vector <string> nameofEnemy;
	vector <int> healthEnemy;
};
class ConsoleView
{

public:
	bool just_numeric_input(string input);
	void print_error(string what);
	void print_map(vector<string> text);
	void print_Help();
	int print_main_menu();
	bool print_ability(int a);
	int print_complet_needs(int c, vector <int> a = {}, vector <string> b = {});
	vector <string> get_name();
	void print_name(string name);
	int print_initial_position(string name);
	int print_action_menu(ShowActionMenu s);
	int print_maneuver();
	int print_move1(vector <int> cell);
	void print_move2(int a);
	int print_move_get_name(vector <string> name);
	vector <int> print_discarding(vector <string> card, vector<string> name);
	int print_scheme(vector <string> s);
	int print_attack1(vector <string> s, int a);
	int print_attack2(vector <string> s, int a);
	void print_error_attack(int a);
	void end_of_game(string a);
	void show_hand(vector <string> s);
	void print_combat_result(int a, string name = "");
	void clear();
};