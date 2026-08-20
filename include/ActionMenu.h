#pragma once
#include <raylib.h>
#include <vector>
#include <string>

class ActionMenu
{
public:

	struct ShowActionMenu
	{
		std::vector <int> healthPlayer1;
		std::vector <int> healthPlayer2;
		std::vector <std::string> cards;
		bool canAttack = 0;
		bool canScheme = 0;
		std::string AttackReason = " ";
		std::string SchemeReason = " ";
		std::vector <Texture2D> cardsPhoto;
		Texture2D thiscard;
		bool is_thiscard = 0;
	};
	struct cell
	{
		float x;
		float y;
		std::string heroPhoto;
		int num;
		Texture2D photo;
	};
public:
	std::vector <std::string> player1;
	std::vector <std::string> player2;
	Font font = LoadFont("../Assets/font.ttf");
	Texture2D backsher;
	Texture2D backdra;
	Texture2D backman;
	ActionMenu();
	~ActionMenu();
	void load_run();
	void load_action();
	void load_cards();
	void unload_run();
	void unload_action();
	void unload_cards();
	void draw_run(int a);
	void load_map(std::vector <cell>& map);
	void unload_map(std::vector <cell>& map);
	void draw_map(std::vector <cell>& map);
	void draw_action();
	void draw_change_turn(int a);
	void draw_cards();
	void draw_winner(int a);
	void load_help();
	void unload_help();
	void draw_help();
	int check_help();
	std::vector <Texture2D> load_cards_action(std::vector <std::string> cards);
	void unload_cards_action(std::vector <Texture2D> cards);
	void draw_cards_action(std::vector <Texture2D> cards);
	ShowActionMenu action;
	int checkAction();
private:

	std::vector <Texture2D> player1photo;
	std::vector <Texture2D> player2photo;
	Texture2D back;
	Texture2D button;
	Texture2D help;
	Texture2D help_text;
	Texture2D fog;


};

