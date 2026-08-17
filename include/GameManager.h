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
	int do_at_end();
	void dracula_ability();
	void initial_position();
	void complet_action_menu();
};

