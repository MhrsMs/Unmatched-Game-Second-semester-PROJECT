#pragma once
#include "Effect.h"
#include "PlayerInformation.h"
#include "Graphics.h"

class Action
{
public :
	Action(Graphics& view);
	Graphics &view;
	Complet_Needs take_needs(PlayerInformation &players, Card& card, Hero* heroteam = nullptr, Hero* herotarget = nullptr);
	void movement(PlayerInformation& players, Hero* hero, int moveMax = 0, int moveMin = 0);
	void movement_fog(PlayerInformation& players, int cell, int movementnum);
	void update_loc(PlayerInformation& players);
};

