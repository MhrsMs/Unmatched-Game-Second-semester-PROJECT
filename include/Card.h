#pragma once
#include <string>
using namespace std;

struct Needs
{
	bool need_location;
	bool need_optional_card;
	bool need_number;
	bool need_team_person;
	bool need_target_person;
	bool need_winner;
};

class Card
{
private:
	int id;
	string card_name;
	int attack_or_defense;
	string name_of_doer;
	int effect_time;
	int boost;
	int number;
	string kind_of_action;
	Needs needs;
public:

	Card(int id, string card_name, int attack_or_defense, string name_of_doer, int effect_time, int boost, int number, string kind_of_action, Needs needs);
	int get_id() const;
	string get_cardName() const;
	int get_attackOrDefense() const;
	string get_nameOfDoer() const;
	int get_effectTime() const;
	int get_boost() const;
	int get_number() const;
	string get_kindOfAction() const;
	Needs get_Needs() const;
	void change_attackOrDefense(int num);

};

