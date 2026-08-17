#pragma once
#include "CardManager.h"
#include "MapManager.h"
#include "Sherlock.h"
#include "Sister.h"
#include "Dracula.h"
#include "DrWatson.h"
#include "InvisibleMan.h"
#include "Hero.h"
#include <memory>
#include <vector>
#include <string>
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
		int which;
		PlayerData* playerHero = nullptr;
		bool isFoggyFirst = 0;
		bool vanish = 0;
	};
	struct HolmesData : public PlayerData
	{
		HolmesData() : PlayerData(2)
		{
			heros.push_back(make_unique<Sherlock>("../Assets/sherlock_cell.png"));
			heros.push_back(make_unique<DrWatson>("../Assets/drwatson.png"));
		}
	};
	struct DraculaData : public PlayerData
	{
		DraculaData() : PlayerData(1)
		{
			heros.push_back(make_unique<Dracula>("../Assets/dracula_cell.png"));
			heros.push_back(make_unique<Sister>("../Assets/sis1.png"));
			heros.push_back(make_unique<Sister>("../Assets/sis2.png"));
			heros.push_back(make_unique<Sister>("../Assets/sis3.png"));
		}
	};
	struct InvisibleManData : public PlayerData
	{
		InvisibleManData() : PlayerData(3)
		{
			heros.push_back(make_unique<InvisibleMan>("../Assets/invisible_man_cell.png"));
		}
	};
	Player player1;
	Player player2;
	MapManager mapmanager;
	vector <string>hero_to_photo(const vector <Hero*>& hero);
	vector <string>card_to_photo(const vector <Card>& card);
	vector <Hero*> unique_to_hero(Player& player);
};

