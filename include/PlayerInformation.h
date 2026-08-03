#pragma once
#include "CardManager.h"
#include "MapManager.h"
#include "Sherlock.h"
#include "Sister.h"
#include "Dracula.h"
#include "DrWatson.h"
#include "Hero.h"
#include <memory>
class PlayerInformation
{
public:

	struct PlayerData
	{
		vector <unique_ptr<Hero>> heros;
		CardManager cards;
		PlayerData(int a) : cards(a) {}
		virtual ~PlayerData() = default;
	};
	struct Player
	{
		int action;
		string name;
		PlayerData* playerHero = nullptr;

	};
	struct HolmesData : public PlayerData
	{
		HolmesData() : PlayerData(2)
		{
			heros.push_back(make_unique<Sherlock>("SH"));
			heros.push_back(make_unique<DrWatson>("DW"));
		}
	};
	struct DraculaData : public PlayerData
	{
		DraculaData() : PlayerData(1)
		{
			heros.push_back(make_unique<Dracula>("DR"));
			heros.push_back(make_unique<Sister>("S1"));
			heros.push_back(make_unique<Sister>("S2"));
			heros.push_back(make_unique<Sister>("S3"));
		}
	};
	Player player1;
	Player player2;
	MapManager mapmanager;
	vector <string> hero_to_name(vector <Hero*> hero);
	vector <string> card_to_name(vector <Card> card);
	vector <Hero*> unique_to_hero(Player player);
};

