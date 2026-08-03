#include "Action.h"
Complet_Needs Action::take_needs(PlayerInformation& players, Card& card, Hero* heroTeam, Hero* heroTarget)
{
	Complet_Needs complet_needs;
	Needs needs = card.get_Needs();
	if (card.get_kindOfAction() != "Scheme")
	{
		complet_needs.targetPerson = heroTarget;
	}
	if (needs.need_target_person)
	{
		if (card.get_id() == 4)
		{
			vector <Hero*> thishero;
			for (auto& x : players.player2.playerHero->heros)
			{
				if (x->is_alive())
				{
					thishero.emplace_back(x.get());
				}
			}
			for (auto& x : players.player1.playerHero->heros)
			{
				if (x->is_alive())
				{
					thishero.emplace_back(x.get());
				}
			}
			int z = view.print_complet_needs(8, {}, players.hero_to_name(thishero));
			complet_needs.targetPerson = thishero[z];
		}
		else
		{
			int z = view.print_complet_needs(8, {}, players.hero_to_name(players.unique_to_hero(players.player2)));
			complet_needs.targetPerson = players.player2.playerHero->heros[z].get();
		}

	}
	if (needs.need_location)
	{
		if (card.get_id() == 1)
		{
			bool dead = false;

			for (auto& x : players.player1.playerHero->heros)
			{
				if (x->get_name() == "SISTER" && !x->is_alive())
				{
					dead = true;
					int choice;
					while (1)
					{
						choice = view.print_complet_needs(1);
						if (players.mapmanager.is_same_zone(players.player1.playerHero->heros[0]->get_position(), choice))
						{
							break;
						}
					}
					players.player1.playerHero->heros[0]->increase_HP(2);
					x->increase_HP(x->get_original_HP());
					players.mapmanager.move(choice, x.get());
					break;
				}
			}
		}
		if (card.get_id() == 2)
		{
			int cell;
			while (1)
			{
				cell = view.print_complet_needs(2);
				if (!players.mapmanager.is_ally_inside(cell, players.player1.playerHero->heros[0].get()) && !players.mapmanager.is_enemy_inside(cell, players.player1.playerHero->heros[0].get()))
				{
					break;
				}
			}
			complet_needs.location = cell;
		}
		if (card.get_id() == 4)
		{
			view.print_complet_needs(3);
			movement(players, complet_needs.targetPerson, 2, 2);
		}
		if (card.get_id() == 15)
		{
			vector <int> first = players.mapmanager.electable_cells(players.player1.playerHero->heros[0]->get_position());
			vector <int> second;
			for (auto x : first)
			{
				if (!players.mapmanager.is_ally_inside(x, players.player1.playerHero->heros[0].get()))
				{
					second.emplace_back(x);
				}
			}
			int m = view.print_complet_needs(9, second);
			complet_needs.location = second[m];
		}
	}
	if (needs.need_number)
	{
		int s = view.print_complet_needs(7);
		complet_needs.number = s;
	}
	if (needs.need_optional_card)
	{
		vector <Card> optionalcard;
		if (card.get_id() == 8)
		{
			int s;
			vector <Card> cards;
			vector <int> c;
			for (auto x : players.player1.playerHero->cards.hand)
			{
				if (x.get_cardName() != card.get_cardName())
				{
					cards.emplace_back(x);
				}
			}
			while (1)
			{
				s = view.print_discarding(players.card_to_name(cards));
				if (s == 0)
				{
					break;
				}
				for (auto x : c)
				{
					if (x == s)
					{
						continue;
					}
				}
				optionalcard.emplace_back(cards[s - 1]);
				c.emplace_back(s);
			}
			complet_needs.optionalCard = optionalcard;
		}
		if (card.get_id() == 13)
		{
			vector <Card> optionalcard;
			int s;
			while (1)
			{
				if (!players.player2.playerHero->cards.hand.empty())
				{
					s = view.print_discarding(players.card_to_name(players.player2.playerHero->cards.hand));
					if (s != 0)
					{
						optionalcard.emplace_back(players.player2.playerHero->cards.hand[s - 1]);
						break;
					}
				}
				else
				{
					break;
				}
			}
			complet_needs.optionalCard = optionalcard;
		}
	}
	return complet_needs;
}

void Action::movement(PlayerInformation& players, Hero* hero, int moveMax, int moveMin)
{
	if (hero == nullptr)
	{
		int b = view.print_move_get_name(players.hero_to_name(players.unique_to_hero(players.player1)));
		hero = players.player1.playerHero->heros[b].get();
		moveMax += hero->get_move();
		view.print_movenumber(moveMax);
	}
	if (moveMax == 0)
	{
		moveMax = hero->get_move();
	}
	int movementnum = 0;
	int position = hero->get_position();
	while (movementnum < moveMax)
	{
		vector <int> cell = players.mapmanager.electable_cells(position);
		vector <int> d;
		if ((moveMax - movementnum) < 2)
		{
			for (auto x : cell)
			{
				if (!players.mapmanager.is_ally_inside(x, hero))
				{
					d.emplace_back(x);
				}
			}
		}
		else
		{
			d = cell;
		}
		if (d.empty())
		{
			throw runtime_error("this hero can not move");
		}
		else
		{
			int a = view.print_move1(d);
			if (a == 0)
			{
				if (movementnum < moveMin)
				{
					view.print_move2(3);
				}
				else
				{
					break;
				}
			}
			else
			{
				if (players.mapmanager.is_ally_inside(d[a - 1], hero))
				{
					view.print_move2(1);

				}
				else
				{
					players.mapmanager.move(d[a - 1], hero);
					view.print_map(players.mapmanager.text_inside_cells());
				}
				movementnum++;
				position = d[a - 1];
			}
		}
	}
}

