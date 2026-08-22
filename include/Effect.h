#pragma once
#include "CardManager.h"
#include "Hero.h"
#include "MapManager.h"
#include "Action.h"
#include "PlayerInformation.h"
#include "xmemory"
struct undo_system
{
	virtual void undo_function() = 0;
	virtual ~undo_system() = default;
};

struct undo_card : public undo_system
{
	int deck_to_hand;
	CardManager& cards;
	int index;
	void undo_function()
	{
		if (deck_to_hand == 1)
		{
			cards.hand_to_deck_BACK();
		}
		else if (deck_to_hand == 0)
		{
			cards.null_card_to_hand_BACK(index);
			cards.hand.back().change_attackOrDefense(0);
		}
		else if (deck_to_hand == 2)
		{
			cards.deck_to_hand(1);
		}
	}
	undo_card(CardManager& cards, bool deck_to_hand, int index = 0) : cards(cards), deck_to_hand(deck_to_hand), index(index) {}

};

struct  undo_hp : public undo_system
{
	Hero* hero;
	bool less_hp;
	int hp;
	void undo_function()
	{
		if (less_hp)
		{
			hero->increase_HP(hp);
		}
		else
		{
			hero->decrease_HP(hp);
		}
	}
	undo_hp(bool less_hp, int hp, Hero* hero) : less_hp(less_hp), hp(hp), hero(hero)
	{
	}

};

struct undo_move_hero : public undo_system
{
	Hero* hero;
	MapManager& mapmanager;
	int position;
	void undo_function()
	{
		mapmanager.move(position, hero);
	}
	undo_move_hero(MapManager& mapmanager, int position, Hero* hero) : position(position), hero(hero), mapmanager(mapmanager) {}
};
struct undo_move_fog : public undo_system
{
	int first_position;
	int second_position;
	MapManager& mapmanager;
	void undo_function()
	{
		mapmanager.set_foggy(first_position, second_position);
	}
	undo_move_fog(MapManager& mapmanager, int second_position, int first_position) : mapmanager(mapmanager), first_position(first_position), second_position(second_position) {}
};
struct undo_action : public undo_system
{
	PlayerInformation players;
	void undo_function()
	{
		--players.player1.action;
	}
	undo_action(PlayerInformation players) : players(players) {}
};
class Effect
{
public:
	inline static vector<vector<unique_ptr<undo_system>>> undo_system_list;

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
	void effect14(Data& data, Complet_Needs& complet_needs);
	void effect15(Data& data, Complet_Needs& complet_needs);
	void effect16(Data& data, Complet_Needs& complet_needs);
};

