#include "Maneuver.h"
#include "Effect.h"
Maneuver::Maneuver(Graphics& view) : Action(view)
{
}
void Maneuver::do_maneuver(PlayerInformation& players)
{
	Effect effect;
	if (players.player1.playerHero->cards.can_deck_to_hand(1))
	{
		players.player1.playerHero->cards.deck_to_hand(1);
		effect.undo_system_list.back().push_back(make_unique<undo_card>(players.player1.playerHero->cards, 1));
	}
	else
	{
		for (auto& x : players.player1.playerHero->heros)
		{
			x->decrease_HP(2);
			effect.undo_system_list.back().push_back(make_unique<undo_hp>(1, 2, x.get()));
		}
	}
	update_loc(players);
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
			if (!players.player1.playerHero->cards.hand.empty())
			{
				update_loc(players);
				int a = view.get_card(3, players.player1.playerHero->cards.hand.size());
				if (a == -2)
				{
					continue;
				}
				boost = boost + players.player1.playerHero->cards.hand[a].get_boost();
				int id = players.player1.playerHero->cards.hand[a].get_id();
				players.player1.playerHero->cards.hand_to_null_card(id);
				effect.undo_system_list.back().push_back(make_unique<undo_card>(players.player1.playerHero->cards, 0, a));
				update_loc(players);
			}
		}
		else if (m == 3)
		{
			break;
		}
	}
}
