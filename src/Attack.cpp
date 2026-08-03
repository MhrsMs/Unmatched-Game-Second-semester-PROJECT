#include "Attack.h"
void Attack::do_attack(PlayerInformation& players)
{
	vector <Hero*> hero1 = players.unique_to_hero(players.player1);
	int attacker;
	vector <Hero*> hero2;
	vector <Card> card1;
	while (1)
	{
		attacker = view.print_attack1(players.hero_to_name(hero1), 1);
		for (auto& x : players.player2.playerHero->heros)
		{
			if (x->is_alive())
			{
				if (hero1[attacker]->get_attack_type() == "melee")
				{
					if (players.mapmanager.is_adjacent(hero1[attacker]->get_position(), x->get_position()))
					{

						hero2.emplace_back(x.get());
					}
				}
				else
				{
					if (players.mapmanager.is_same_zone(hero1[attacker]->get_position(), x->get_position()) || players.mapmanager.is_adjacent(hero1[attacker]->get_position(), x->get_position()))
					{
						hero2.emplace_back(x.get());
					}
				}
			}
		}
		if (hero2.empty())
		{
			view.print_error_attack(1);
		}
		else
		{
			card1 = players.player1.playerHero->cards.get_cards_by_action(2, hero1[attacker]);
			if (card1.empty())
			{
				view.print_error_attack(2);
			}
			else
			{
				break;
			}
		}
	}
	int defender = view.print_attack1(players.hero_to_name(hero2), 2);
	int ca1 = view.print_attack2(players.card_to_name(card1), 1);
	vector <Card> card2 = players.player2.playerHero->cards.get_cards_by_action(3, hero2[defender]);
	bool df = 1;
	int ca2;
	if (card2.empty())
	{
		df = 0;
	}
	else
	{
		view.print_name(players.player2.name);
		ca2 = view.print_attack2(players.card_to_name(card2), 2);
		if (ca2 == 0)
		{
			df = 0;
		}
		else
		{
			ca2 = ca2 - 1;
		}
	}
	Complet_Needs complet1 = take_needs(players, card1[ca1], hero1[attacker], hero2[defender]);
	Complet_Needs complet2;
	Data data1{ hero1,players.unique_to_hero(players.player2),players.player1.playerHero->cards,players.player2.playerHero->cards,players.mapmanager,*hero1[attacker],&card1[ca1],nullptr };
	Data data2{ players.unique_to_hero(players.player2),hero1,players.player2.playerHero->cards,players.player1.playerHero->cards,players.mapmanager,*hero2[defender],nullptr,&card1[ca1] };
	if (df)
	{
		complet2 = take_needs(players, card2[ca2], hero2[defender], hero1[attacker]);
		data1.targetcard = &card2[ca2];
		data2.thiscard = &card2[ca2];
	}
	Effect effect;
	bool farib1 = 0;
	bool farib2 = 0;
	if (df)
	{
		if (card2[ca2].get_id() == 23 || card2[ca2].get_id() == 10)
		{
			if (card1[ca1].get_nameOfDoer() != "SHERLOCK" && card1[ca1].get_nameOfDoer() != "DR.WATSON")
			{
				farib2 = 1;
			}

		}
		if (card2[ca2].get_id() == 25)
		{
			if (complet2.number == card1[ca1].get_attackOrDefense())
			{
				farib2 = 1;
				card1[ca1].change_attackOrDefense(-card1[ca1].get_attackOrDefense());
			}
		}
	}
	if (card1[ca1].get_id() == 23 || card1[ca1].get_id() == 10)
	{
		if (df)
		{
			if (card2[ca2].get_nameOfDoer() != "SHERLOCK" && card2[ca2].get_nameOfDoer() != "DR.WATSON")
			{
				farib1 = 1;
			}
		}

	}
	if (df)
	{
		if (card2[ca2].get_effectTime() == 1 && !farib1)
		{
			effect.apply_effect(card2[ca2].get_id(), data2, complet2);
		}
	}

	if (card1[ca1].get_effectTime() == 1 && !farib2)
	{
		effect.apply_effect(card1[ca1].get_id(), data1, complet1);
	}
	if (df)
	{
		if (card2[ca2].get_effectTime() == 2 && !farib1)
		{
			effect.apply_effect(card2[ca2].get_id(), data2, complet2);
		}
	}

	if (card1[ca1].get_effectTime() == 2 && !farib2)
	{
		effect.apply_effect(card1[ca1].get_id(), data1, complet1);
	}
	int defensenumber = 0;
	if (df)
	{
		defensenumber = card2[ca2].get_attackOrDefense();
	}
	if (card1[ca1].get_attackOrDefense() > defensenumber)
	{
		int damage = card1[ca1].get_attackOrDefense() - defensenumber;
		hero2[defender]->decrease_HP(damage);
		if (card1[ca1].get_id() == 24)
		{
			view.show_hand(players.card_to_name(players.player2.playerHero->cards.hand));
		}
		complet1.heroWin = 1;
		if (df)
		{
			complet2.heroWin = 0;
		}
		if (card1[ca1].get_id() == 7)
		{
			{
				vector <int> first = players.mapmanager.electable_cells(hero2[defender]->get_position());
				vector <int> second;
				for (auto x : first)
				{
					if (!players.mapmanager.is_ally_inside(x, hero2[defender]))
					{
						second.emplace_back(x);
					}
				}
				int k = view.print_complet_needs(4, second);
				players.mapmanager.move(second[k], players.player1.playerHero->heros[0].get());
			}
		}
		view.print_combat_result(1, damage);
	}

	else
	{
		if (card2[ca2].get_id() == 24)
		{
			view.show_hand(players.card_to_name(players.player1.playerHero->cards.hand));
		}
		complet1.heroWin = 0;
		if (df)
		{
			complet2.heroWin = 1;
		}

		view.print_combat_result(2);
	}
	if (df)
	{
		if (card2[ca2].get_effectTime() == 3 && !farib1)
		{
			effect.apply_effect(card2[ca2].get_id(), data2, complet2);
			if (card2[ca2].get_id() == 9)
			{
				if (hero2[defender]->is_alive())
				{
					view.print_complet_needs(5);
					movement(players, hero2[defender], 3, 3);
				}
			}
		}
	}
	if (card1[ca1].get_effectTime() == 3 && !farib2)
	{
		effect.apply_effect(card1[ca1].get_id(), data1, complet1);
		if (card1[ca1].get_id() == 9 || card1[ca1].get_id() == 18)
		{
			if (hero1[attacker]->is_alive())
			{
				view.print_complet_needs(5);
				movement(players, hero1[attacker], 3, 3);
			}
		}

	}
	players.player1.playerHero->cards.hand_to_null_card(card1[ca1].get_id());
	if (df)
	{
		players.player2.playerHero->cards.hand_to_null_card(card2[ca2].get_id());
	}
}
int Attack::can_attack(PlayerInformation& players)
{
	vector <Card> mainhero = players.player1.playerHero->cards.get_cards_by_action(2, players.player1.playerHero->heros[0].get());
	vector <Card> otherhero;
	vector <Hero*> hero;
	if (players.player1.playerHero->heros[1]->is_alive())
	{
		otherhero = players.player1.playerHero->cards.get_cards_by_action(2, players.player1.playerHero->heros[1].get());
	}
	if (mainhero.empty() && otherhero.empty())
	{
		return 0;
	}

	bool found = false;
	for (int i = 0; i < players.player1.playerHero->heros.size() && !found; i++)
	{
		if (players.player1.playerHero->heros[i]->is_alive())
		{
			if (players.player1.playerHero->heros[i]->get_attack_type() == "melee")
			{
				for (auto& x : players.player2.playerHero->heros)
				{
					if (x->is_alive())
					{
						if (players.mapmanager.is_adjacent(x->get_position(), players.player1.playerHero->heros[i]->get_position()))
						{
							hero.emplace_back(x.get());
						}
					}
				}
				if (!hero.empty())
				{
					found = true;
				}
			}
			else
			{
				for (auto& x : players.player2.playerHero->heros)
				{
					if (x->is_alive())
					{
						if (players.mapmanager.is_same_zone(x->get_position(), players.player1.playerHero->heros[i]->get_position()) || players.mapmanager.is_adjacent(x->get_position(), players.player1.playerHero->heros[i]->get_position()))
						{
							hero.emplace_back(x.get());
						}
					}
				}
			}
		}
	}
	if (hero.empty())
	{
		return 2;
	}
	return 1;
}

