#pragma once
#include "CardManager.h"
#include "Hero.h"
#include "MapManager.h"
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
};
class Effect
{
public:

	void apply_effect(int id, Data& data, Complet_Needs complet_needs);
	int rm(int min, int max);
	void effect1(int a, Data& data, Complet_Needs& complet_needs);
	void effect2(int a, Data& data, Complet_Needs& complet_needs);
	void effect3(Data& data, Complet_Needs& complet_needs);
	void effect5(Data& data, Complet_Needs& complet_needs);
	void effect7(Data& data, Complet_Needs& complet_needs);
	void effect8(Data& data, Complet_Needs& complet_needs);
	void effect9(Data& data, Complet_Needs& complet_needs);
	void effect10(Data& data, Complet_Needs& complet_needs);
	void effect11(Data& data, Complet_Needs& complet_needs);
	void effect12(Data& data, Complet_Needs& complet_needs);
	void effect13(Data& data, Complet_Needs& complet_needs);
};

