#pragma once
#include "PlayerInformation.h"
#include "Graphics.h"


struct Data
{
	vector <Hero*> team;
	vector <Hero*> target;
	CardManager& cardsTeam;
	CardManager& cardsTarget;
	MapManager& mapManager;
	Hero& actor;
	Card* thiscard = nullptr;
	Card* targetcard = nullptr;

};
struct Complet_Needs
{
	vector <Card> optionalCard = {};
	int location = 0;
	int number = 0;
	bool heroWin = 0;
	Hero* teamPerson = nullptr;
	Hero* targetPerson = nullptr;
	bool is_foggy = 0;
};
class Action
{

public:
	Action(Graphics& view);
	Graphics& view;
	Complet_Needs take_needs(PlayerInformation& players, Card& card, Hero* heroteam = nullptr, Hero* herotarget = nullptr);
	void movement(PlayerInformation& players, Hero* hero, int moveMax = 0, int moveMin = 0);
	void movement_fog(PlayerInformation& players, int cell, int movementnum);
	void update_loc(PlayerInformation& players);
};

