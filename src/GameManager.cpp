#include "GameManager.h"

void GameManager::do_at_fisrt()
{
	players.player1.action = 2;
	players.player2.action = 2;
	while (players.player2.playerHero->cards.hand.size() > 7)
	{
		int a = view.print_discarding(players.card_to_name(players.player2.playerHero->cards.hand));
		players.player2.playerHero->cards.hand_to_null_card(players.player2.playerHero->cards.hand[a - 1].get_id());
	}
}

int GameManager::do_at_end()
{
	if (!players.player1.playerHero->heros[0]->is_alive())
	{
		view.end_of_game(players.player2.name);
		return 1;
	}
	if (!players.player2.playerHero->heros[0]->is_alive())
	{
		view.end_of_game(players.player1.name);
		return 2;
	}
	auto& heros1 = players.player1.playerHero->heros;
	stable_partition(heros1.begin() + 1, heros1.end(), [](const auto& hero)
		{
			return hero && hero->is_alive();
		});
	auto& heros2 = players.player2.playerHero->heros;
	stable_partition(heros2.begin() + 1, heros2.end(), [](const auto& hero)
		{
			return hero && hero->is_alive();
		});
	return 0;
}

void GameManager::dracula_ability()
{
	view.print_map(players.mapmanager.text_inside_cells());
	bool b = view.print_ability(1);
	if (b)
	{
		vector <Hero*> hero = players.mapmanager.nearby_heroes(players.player1.playerHero->heros[0]->get_position());
		if (!hero.empty())
		{
			vector <Hero*> hero1;
			for (auto& x : players.player1.playerHero->heros)
			{
				hero1.emplace_back(x.get());
			}
			int z = view.print_complet_needs(8, {}, players.hero_to_name(hero));
			players.player1.playerHero->heros[0]->ability(*hero[z], hero1, players.player1.playerHero->cards);
		}
		else
		{
			view.print_ability(2);
		}
	}
}

void GameManager::initial_position()
{
	players.mapmanager.move(22, players.player1.playerHero->heros[0].get());
	players.mapmanager.move(9, players.player2.playerHero->heros[0].get());
	view.print_map(players.mapmanager.text_inside_cells());

	vector <int> p1;
	vector <int> p2;
	for (auto& x : players.player1.playerHero->heros)
	{
		if (x->get_position() == 0)
		{
			while (1)
			{
				if (x->get_name() == "SISTER")
				{
					int p = view.print_initial_position(x->get_name() + " " + x->get_short_name());
					if (players.mapmanager.is_same_zone(22, p) && !players.mapmanager.is_ally_inside(p, x.get()) && !players.mapmanager.is_enemy_inside(p, x.get()))
					{
						players.mapmanager.move(p, x.get());
						break;
					}
				}
				else
				{
					int p = view.print_initial_position(x->get_name());
					if (players.mapmanager.is_same_zone(22, p) && !players.mapmanager.is_ally_inside(p, x.get()) && !players.mapmanager.is_enemy_inside(p, x.get()))
					{
						players.mapmanager.move(p, x.get());
						break;
					}
				}

			}

		}
	}
	for (auto& x : players.player2.playerHero->heros)
	{
		if (x->get_position() == 0)
		{
			while (1)
			{
				if (x->get_name() == "SISTER")
				{
					int p = view.print_initial_position(x->get_name() + " " + x->get_short_name());
					if (players.mapmanager.is_same_zone(9, p) && !players.mapmanager.is_ally_inside(p, x.get()) && !players.mapmanager.is_enemy_inside(p, x.get()))
					{
						players.mapmanager.move(p, x.get());
						break;
					}
				}
				else
				{
					int p = view.print_initial_position(x->get_name());
					if (players.mapmanager.is_same_zone(9, p) && !players.mapmanager.is_ally_inside(p, x.get()) && !players.mapmanager.is_enemy_inside(p, x.get()))
					{
						players.mapmanager.move(p, x.get());
						break;
					}
				}

			}

		}
	}

}

ShowActionMenu GameManager::complet_action_menu()
{
	ShowActionMenu show;
	Attack action1;
	Scheme action2;
	int attack = action1.can_attack(players);
	if (attack == 0)
	{
		show.attack = false;
		show.attackReason = "No active cards available for attack";
	}
	else if (attack == 1)
	{
		show.attack = true;
	}
	else if (attack == 2)
	{
		show.attack = false;
		show.attackReason = "No enemy available for attack";
	}
	int scheme = action2.can_scheme(players);
	if (scheme == 2)
	{
		show.scheme = false;
		show.schemeReason = "No active cards available for scheme";
	}
	else if (scheme == 1)
	{
		show.scheme = true;
	}
	else if (scheme == 0)
	{
		show.scheme = false;
		show.schemeReason = "No cards have a living owner for scheme";
	}
	for (auto& x : players.player1.playerHero->heros)
	{
		show.nameOfHero.emplace_back(x->get_name());
		show.health.emplace_back(x->get_HP());
		show.move.emplace_back(x->get_move());
		show.cell.emplace_back(x->get_position());
	}
	for (auto x : players.player1.playerHero->cards.hand)
	{
		show.card.emplace_back(x.get_cardName());
		show.kind.emplace_back(x.get_kindOfAction());
		show.nameOfDoer.emplace_back(x.get_nameOfDoer());
	}
	for (auto& x : players.player2.playerHero->heros)
	{
		show.nameofEnemy.emplace_back(x->get_name());
		show.healthEnemy.emplace_back(x->get_HP());
	}

	show.name = players.player1.name;
	show.text = players.mapmanager.text_inside_cells();;
	return show;
}

void GameManager::run()
{
	while (1)
	{
		int mainMenu = view.print_main_menu();
		if (mainMenu == 1)
		{
			try
			{
				vector <string> name = view.get_name();
				players.player1.name = name[0];
				players.player2.name = name[1];
				if (name[2] == "1")
				{
					players.player1.playerHero = &draculadata;
					players.player2.playerHero = &holmesdata;
				}
				else
				{
					players.player1.playerHero = &holmesdata;
					players.player2.playerHero = &draculadata;
				}
				initial_position();
				while (1)
				{
					try
					{
						bool exit = false;
						do_at_fisrt();
						if (players.player1.playerHero->heros[0]->get_name() == "DRACULA")
						{
							dracula_ability();
						}
						for (int i = 0; i < players.player1.action; i++)
						{
							int choice;
							while (1)
							{
								int choice1 = view.print_action_menu(complet_action_menu());
								if (choice1 == 2)
								{
									view.clear();
								}
								else
								{
									choice = choice1;
									break;
								}
							}
							if (choice == 1)
							{
								exit = true;
								break;
							}
							switch (choice)
							{
							case 3:
							{
								Maneuver maneuver;
								maneuver.do_maneuver(players);
								break;
							}
							case 4:
							{
								Scheme scheme;
								scheme.do_scheme(players);
								break;
							}

							case 5:
							{
								Attack attack;
								attack.do_attack(players);
								break;
							}
							}
							int x = do_at_end();
							if (x != 0)
							{
								break;
								exit = true;
							}

						}
						if (exit)
						{
							break;
						}
						PlayerInformation::Player player = players.player1;
						players.player1 = players.player2;
						players.player2 = player;
					}
					catch (exception& e)
					{
						view.print_error(e.what());
					}
				}
			}
			catch (exception& e)
			{
				view.print_error(e.what());
			}
		}
		else if (mainMenu == 2)
		{
			view.print_Help();
		}
		else if (mainMenu == 3)
		{
			break;
		}
	}
}

