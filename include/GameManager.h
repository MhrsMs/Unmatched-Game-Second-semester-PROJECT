#pragma once
#include "CardManager.h"
#include "MapManager.h"
#include "Hero.h"
#include "Dracula.h"
#include "Sister.h"
#include "Sherlock.h"
#include "DrWatson.h"
#include "Effect.h"
#include "ConsoleView.h"
#include <exception>
#include <memory>

class GameManager
{
private:

	ConsoleView view;
	struct PlayerData
	{
		vector <unique_ptr<Hero>> heros;
		CardManager cards;
		PlayerData(int a) : cards(a) {}
		virtual ~PlayerData() = default;
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
	struct Player
	{
		int action;
		string name;
		PlayerData* playerHero = nullptr;
	};
	HolmesData holmesdata;
	DraculaData draculadata;
	MapManager mapmanager;
public:
	GameManager() = default;
	void run();
	void do_at_fisrt(Player& player1, Player& player2);
	int do_at_end(Player& player1, Player& player2);
	void maneuver(Player& player1, Player& player2);
	void scheme(Player& player1, Player& player2);
	void attack(Player& player1, Player& player2);
	Complet_Needs take_needs(Player& player1, Player& funplayer2, Card& card, Hero* heroteam = nullptr, Hero* herotarget = nullptr);
	void movement(Player* funplayer1, Hero* hero, int moveMax = 0, int moveMin = 0);
	void initial_position(Player& funplayer1, Player& funplayer2);
	ShowActionMenu complet_action_menu(Player& funplayer1, Player& funplayer2);
	int can_scheme(Player& player1, Player& player2);
	int can_attack(Player& player1, Player& player2);
	vector <string> hero_to_name(vector <Hero*> hero);
	vector <string> card_to_name(vector <Card> card);
	vector <Hero*> unique_to_hero(Player player);
};

