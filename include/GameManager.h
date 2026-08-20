#pragma once
#include "CardManager.h"
#include "MapManager.h"
#include "Action.h"
#include "Scheme.h"
#include "Attack.h"
#include "Maneuver.h"
#include "Graphics.h"
#include <exception>
#include <algorithm>
class GameManager
{
private:

	Graphics view;
	PlayerInformation players;
	PlayerInformation::HolmesData holmesdata;
	PlayerInformation::DraculaData draculadata;
	PlayerInformation::InvisibleManData invisiblemandata;


public:
	GameManager() = default;
	void run();
	void do_at_fisrt();
	void check_every_round();
	int check_every_action();
	void dracula_ability();
	void initial_position();
	void complete_action_menu();
	void complete_for_save_game();
	void load_save_game(int which_save);
	void run_game_action();
	void match_heros(int nameOfHero1, int nameOfHero2);
};

