#include "Dracula.h"
using namespace std;

Dracula::Dracula(string short_name) : Hero(short_name, "DRACULA", 13, 2, "melee") {}

void Dracula::ability(Hero& hero, vector <Hero*> heros, CardManager& card)
{
	hero.decrease_HP(1);

	if (card.can_deck_to_hand(1))
	{
		card.deck_to_hand(1);
	}
	else
	{
		for (auto x : heros)
		{
			x->decrease_HP(2);
		}
	}
}