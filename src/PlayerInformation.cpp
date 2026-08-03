#include "PlayerInformation.h"
vector<string> PlayerInformation::hero_to_name(vector <Hero*> hero)
{
	vector <string> s;
	for (auto x : hero)
	{
		if (x->get_name() == "SISTER")
		{
			s.emplace_back(x->get_name() + " " + x->get_short_name());
		}
		else
		{
			s.emplace_back(x->get_name());
		}
	}
	return s;
}

vector<string> PlayerInformation::card_to_name(vector<Card> card)
{
	vector <string> s;
	for (auto x : card)
	{
		s.emplace_back(x.get_cardName());
	}
	return s;
}

vector<Hero*> PlayerInformation::unique_to_hero(Player player)
{
	vector <Hero*> hero;
	for (auto& x : player.playerHero->heros)
	{
		if (x->is_alive())
		{
			hero.emplace_back(x.get());
		}
	}
	return hero;
}
