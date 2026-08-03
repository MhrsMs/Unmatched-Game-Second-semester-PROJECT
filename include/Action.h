#pragma once
#include "Effect.h"
#include "PlayerInformation.h"
#include "ConsoleView.h"
class Action
{
public:

	ConsoleView view;
	Complet_Needs take_needs(PlayerInformation& players, Card& card, Hero* heroteam = nullptr, Hero* herotarget = nullptr);
	void movement(PlayerInformation& players, Hero* hero, int moveMax = 0, int moveMin = 0);
};

