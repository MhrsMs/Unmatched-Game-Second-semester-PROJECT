#include "Maneuver.h"
Maneuver::Maneuver(Graphics& view) : Action(view)
{
}
void Maneuver::do_maneuver(PlayerInformation& players)
{
	if (players.player1.playerHero->cards.can_deck_to_hand(1))
	{
		players.player1.playerHero->cards.deck_to_hand(1);
		update_loc(players);
	}
	else
	{
		for (auto& x : players.player1.playerHero->heros)
		{
			x->decrease_HP(2);
		}
	}
	int boost = 0;
	while (1)
	{
		int m = view.maneuver();
		if (m == 1)
		{
			movement(players, nullptr, boost);
			break;
		}
		else if (m == 2)
		{
			int a = view.get_card(3,players.player1.playerHero->cards.hand.size());
			if (a == -2)
			{
				continue;
			}
			boost = boost + players.player1.playerHero->cards.hand[a].get_boost();
			int id = players.player1.playerHero->cards.hand[a].get_id();
			players.player1.playerHero->cards.hand_to_null_card(id);
			update_loc(players);
		}
		
		else if (m == 3)
		{
			break;
		}
	}
}
