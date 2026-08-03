#include "Maneuver.h"
void Maneuver::do_maneuver(PlayerInformation& players)
{
	if (players.player1.playerHero->cards.can_deck_to_hand(1))
	{
		players.player1.playerHero->cards.deck_to_hand(1);
		view.print_hand_cards(players.card_to_name(players.player1.playerHero->cards.hand));
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
		int m = view.print_maneuver();
		if (m == 1)
		{
			movement(players, nullptr, boost);
			break;
		}
		else if (m == 2)
		{
			int a = view.print_discarding(players.card_to_name(players.player1.playerHero->cards.hand));
			if (a == 0)
			{
				continue;
			}
			boost = boost + players.player1.playerHero->cards.hand[a - 1].get_boost();
			int id = players.player1.playerHero->cards.hand[a - 1].get_id();
			players.player1.playerHero->cards.hand_to_null_card(id);
		}
		else if (m == 3)
		{
			break;
		}
	}
}
