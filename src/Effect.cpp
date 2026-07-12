#include "Effect.h"
#include <random>

void Effect::apply_effect(int id, Data data, Complet_Needs complet_needs)
{
	switch (id)
	{
	case 1:effect4(data, complet_needs); break;
	case 2:effect11(data, complet_needs); break;
	case 3:effect5(data, complet_needs); break;
	case 4:effect3(data, complet_needs); break;
	case 5:effect2(1, data, complet_needs); break;
	case 6:effect2(4, data, complet_needs); break;
	case 7:effect6(data, complet_needs); break;
	case 8:effect2(2, data, complet_needs); break;
	case 11:effect2(3, data, complet_needs); break;
	case 12:effect1(1, data, complet_needs); break;
	case 13:effect12(data, complet_needs); break;
	case 14:effect7(data, complet_needs); break;
	case 15:effect1(2, data, complet_needs); break;
	case 19:effect13(data, complet_needs); break;
	case 20:effect9(data, complet_needs); break;
	case 21:effect10(data, complet_needs); break;
	case 22:effect8(data, complet_needs); break;
	default: break;
	}
}
int Effect::rm(int min, int max)
{
	static std::mt19937
		gen(std::random_device{}());
	std::uniform_int_distribution<int>
		dist(min, max);
	return dist(gen);
}
void Effect::effect1(int a, Data data, Complet_Needs complet_needs)
{
	//1=bahre bardari 2 = emdad resani
	if (a == 2)
	{
		data.mapManager.move(complet_needs.location, data.team[1]);
	}
	if (data.cardsTeam.can_deck_to_hand(1))
	{
		data.cardsTeam.deck_to_hand(1);
	}
	else
	{
		for (auto x : data.team)
		{
			x->decrease_HP(2);
		}
	}
}
void Effect::effect2(int b, Data data, Complet_Needs complet_needs)
{
	//1 = kamin 2 =form hayola 3=be cheshmanam negah kon 4 = atash khon
	int id;
	int increase;
	if (b == 1)
	{
		if (!data.cardsTarget.hand.empty())
		{
			int a = rm(1, data.cardsTarget.hand.size());
			int boost = data.cardsTarget.hand[a].get_boost();
			data.cardsTarget.hand_to_null_card(data.cardsTarget.hand[a].get_id());
			*(data.damage) = boost + 2;
		}
	}
	if (b == 2)
	{
		int a = complet_needs.optionalCard.size();
		*(data.damage) = a + 6;
	}
	if (b == 3)
	{
		int a = data.targetcard->get_boost();
		*(data.damage) = a + 1;
	}
	if (b == 4)
	{
		for (int i = 1; i < 4; i++)
		{
			if (data.team[i]->is_alive())
			{
				if (data.mapManager.is_same_zone(complet_needs.targetPerson->get_position(), data.team[i]->get_position()))
				{
					data.damage++;
				}
			}
		}
	}
}


void Effect::effect3(Data data, Complet_Needs complet_needs)
{
	//eqvay siri napazir
	vector <Hero*> h = data.mapManager.nearby_heroes(complet_needs.targetPerson->get_position());
	for (auto x : h)
	{
		if (x->get_name() == "SISTER")
		{
			complet_needs.targetPerson->decrease_HP(1);
		}
	}

}
void Effect::effect4(Data data, Complet_Needs complet_needs)
{
	//qosle khon 
	data.actor.increase_HP(2);
	bool found = false;
	for (auto x : data.team)
	{
		if (!x->is_alive() && !found)
		{
			x->increase_HP(x->get_original_HP());
			data.mapManager.move(complet_needs.location, x);
			found = true;
		}
	}
}

void Effect::effect5(Data data, Complet_Needs complet_needs)
{
	//shekar kon
	vector <Hero*> h = data.mapManager.nearby_heroes(data.actor.get_position());
	for (auto x : h)
	{
		if (x->get_name() == "SHERLOCK" || x->get_name() == "DR.WATSON")
		{
			x->decrease_HP(1);
			data.actor.increase_HP(1);
		}
	}
}


void Effect::effect6(Data data, Complet_Needs complet_needs)
{
	//teshnegi baray baqa
	if (complet_needs.heroWin)
	{
		data.mapManager.move(complet_needs.location, data.team[1]);
	}
}
void Effect::effect7(Data data, Complet_Needs complet_needs)
{
	//ostad taqir chehre

	int hPosition = data.team[0]->get_position();
	int tPosition = complet_needs.targetPerson->get_position();
	data.mapManager.move(0, data.team[0]);
	data.mapManager.move(hPosition, complet_needs.targetPerson);
	data.mapManager.move(tPosition, data.team[1]);
	complet_needs.targetPerson->decrease_HP(1);
}
void Effect::effect8(Data data, Complet_Needs complet_needs)
{
	//amozesh hargez payan nadarad
	if (complet_needs.heroWin)
	{
		if (data.cardsTarget.can_deck_to_hand(1))
		{
			data.cardsTarget.deck_to_hand(1);
		}
		else
		{
			for (auto x : data.target)
			{
				x->decrease_HP(2);
			}
		}
	}
	else
	{
		for (int i = 0; i < 1; i++)
		{
			if (data.cardsTeam.can_deck_to_hand(1))
			{
				data.cardsTeam.deck_to_hand(1);
			}
			else
			{
				for (auto x : data.team)
				{
					x->decrease_HP(2);
				}
			}
		}

	}
}

void Effect::effect9(Data data, Complet_Needs complet_needs)
{
	//zed hamle
	if (data.mapManager.is_adjacent(data.team[0]->get_position(), complet_needs.targetPerson->get_position()))
	{
		complet_needs.targetPerson->decrease_HP(2);
	}
}
void Effect::effect10(Data data, Complet_Needs complet_needs)
{
	//noqtei sabet dar zamanei moteqaier
	if ((data.team[0]->get_position()), (data.team[1]->get_position()))
	{
		data.team[0]->increase_HP(1);
		data.team[1]->increase_HP(1);
	}
}

void Effect::effect11(Data data, Complet_Needs complet_needs)
{
	//form meh
	data.mapManager.move(complet_needs.location, data.team[0]);
}

void Effect::effect12(Data data, Complet_Needs complet_needs)
{
	//hazfe namomken ha
	int id = complet_needs.optionalCard[0].get_id();
	data.cardsTarget.hand_to_null_card(id);
}

void Effect::effect13(Data data, Complet_Needs complet_needs)
{
	//stentag sterategik
	*(data.damage) = data.targetcard->get_boost();
}
