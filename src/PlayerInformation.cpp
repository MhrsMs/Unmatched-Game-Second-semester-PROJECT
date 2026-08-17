#include "PlayerInformation.h"
using namespace std;
vector<string> PlayerInformation::hero_to_photo(const vector <Hero*> &hero)
{
	vector <string> s;
	for (auto &x : hero)
	{
		s.emplace_back(x->get_photo());
	}
	return s;
}

vector<string> PlayerInformation::card_to_photo(const vector<Card> &card)
{
	vector <string> s;
	for (auto x : card)
	{
		s.emplace_back(x.get_cardPhoto());
	}
	return s;
}

vector<Hero*> PlayerInformation::unique_to_hero(Player & player)
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
