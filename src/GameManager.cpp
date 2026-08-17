#include "GameManager.h"

void GameManager::do_at_fisrt()
{
	players.player1.action = 2;
	players.player2.action = 2;
	while (players.player2.playerHero->cards.hand.size() > 7)
	{
		int a = view.get_card(1, players.player2.playerHero->cards.hand.size());
		players.player2.playerHero->cards.hand_to_null_card(players.player2.playerHero->cards.hand[a - 1].get_id());
	}
}

int GameManager::do_at_end()
{
	if (!players.player1.playerHero->heros[0]->is_alive())
	{
		view.end_game(players.player1.which);
		return 1;
	}
	if (!players.player2.playerHero->heros[0]->is_alive())
	{
		view.end_game(players.player2.which);
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

	int b = view.ability();
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

			int z = view.get_hero(4, players.hero_to_photo(hero));
			players.player1.playerHero->heros[0]->ability(*hero[z], hero1, players.player1.playerHero->cards);
		}
		else
		{
			view.text(1);
		}
	}
}

void GameManager::initial_position()
{
	players.mapmanager.move(22, players.player1.playerHero->heros[0].get());
	players.mapmanager.move(9, players.player2.playerHero->heros[0].get());
	Action ac(view);
	ac.update_loc(players);
	vector <ActionMenu::cell> same_zone1;
	vector <ActionMenu::cell> same_zone2;
	for (int i = 1; i < 33; i++)
	{
		if (players.mapmanager.is_same_zone(22, i) && i != 22)
		{
			ActionMenu::cell c;
			c.num = i;
			c.x = players.mapmanager.get_cell(c.num)->get_x();
			c.y = players.mapmanager.get_cell(c.num)->get_y();
			same_zone1.emplace_back(c);
		}
		if (players.mapmanager.is_same_zone(9, i) && i != 9)
		{
			ActionMenu::cell c;
			c.num = i;
			c.x = players.mapmanager.get_cell(c.num)->get_x();
			c.y = players.mapmanager.get_cell(c.num)->get_y();
			same_zone2.emplace_back(c);
		}
	}
	int n = 4;
	if (players.player1.playerHero->heros[0]->get_name() == "INVISIBLE_MAN")
	{
		ActionMenu::cell c;
		c.num = 22;
		c.x = players.mapmanager.get_cell(c.num)->get_x();
		c.y = players.mapmanager.get_cell(c.num)->get_y();
		same_zone1.emplace_back(c);
		ac.update_loc(players);
		for (int i = 1; i < n; i++)
		{
			int f = view.movement1(5, same_zone1, "", 0);
			if (f > 0)
			{
				players.mapmanager.set_foggy(same_zone1[f].num);
				same_zone1.erase(same_zone1.begin() + f);
			}
			else
			{
				++n;
			}
			ac.update_loc(players);
		}
	}
	else
	{
		for (auto& x : players.player1.playerHero->heros)
		{
			if (x->get_position() == 0)
			{
				while (1)
				{
					int f = view.movement1(1, same_zone1, x->get_name(), 0);
					if (f > 0)
					{
						players.mapmanager.move(same_zone1[f].num, x.get());
						same_zone1.erase(same_zone1.begin() + f);
						break;
					}

				}
			}
			ac.update_loc(players);
		}
	}
	if (players.player2.playerHero->heros[0]->get_name() == "INVISIBLE_MAN")
	{
		ActionMenu::cell c;
		c.num = 9;
		c.x = players.mapmanager.get_cell(c.num)->get_x();
		c.y = players.mapmanager.get_cell(c.num)->get_y();
		same_zone2.emplace_back(c);
		ac.update_loc(players);
		for (int i = 1; i < n; i++)
		{
			int f = view.movement1(5, same_zone2, "", 0);
			if (f > 0)
			{
				players.mapmanager.set_foggy(same_zone2[f].num);
				same_zone2.erase(same_zone2.begin() + f);
			}
			else
			{
				++n;
			}
			ac.update_loc(players);
		}
	}
	else
	{
		for (auto& x : players.player2.playerHero->heros)
		{
			if (x->get_position() == 0)
			{
				while (1)
				{
					int f = view.movement1(1, same_zone2, x->get_name(), 0);
					if (f > 0)
					{
						players.mapmanager.move(same_zone2[f].num, x.get());
						same_zone2.erase(same_zone2.begin() + f);
						break;
					}

				}
			}
			ac.update_loc(players);
		}
	}

}

/*
void GameManager::initial_position()
{
	players.mapmanager.move(22, players.player1.playerHero->heros[0].get());
	players.mapmanager.move(9, players.player2.playerHero->heros[0].get());
	Action ac(view);
	ac.update_loc(players);
	vector <int> fog = { 0,0,0 };
	vector <int> p1;
	vector <int> p2;
	if (players.player1.playerHero->heros[0]->get_name() == "INVISIBLE_MAN")
	{
		for (int i = 1; i < 4; i++)
		{
			while (1)
			{
				int p = view.movement2(1,"Fog " + to_string(i),0);
				if (players.mapmanager.is_same_zone(22, p) && !players.mapmanager.is_foggy(p))
				{
					players.mapmanager.set_foggy(p);
					break;
				}
			}
			ac.update_loc(players);
		}

	}
	else
	{
		for (auto& x : players.player1.playerHero->heros)
		{
			if (x->get_position() == 0)
			{
				while (1)
				{
					int p = view.movement2(1,x->get_name(),0);
					if (players.mapmanager.is_same_zone(22, p) && !players.mapmanager.is_ally_inside(p, x.get()) && !players.mapmanager.is_enemy_inside(p, x.get()))
					{
						players.mapmanager.move(p, x.get());
						break;
					}

				}

			}
			ac.update_loc(players);
		}
	}
	if (players.player2.playerHero->heros[0]->get_name() == "INVISIBLE_MAN")
	{
		for (int i = 1; i < 4; i++)
		{
			while (1)
			{
				int p = view.movement2(1,"Fog " + to_string(i),0);
				if (players.mapmanager.is_same_zone(9, p) && !players.mapmanager.is_foggy(p))
				{
					players.mapmanager.set_foggy(p);
					break;
				}
			}
			ac.update_loc(players);
		}

	}
	else
	{
		for (auto& x : players.player2.playerHero->heros)
		{
			if (x->get_position() == 0)
			{
				while (1)
				{
					int p = view.movement2(1,x->get_name(),0);
					if (players.mapmanager.is_same_zone(9, p) && !players.mapmanager.is_ally_inside(p, x.get()) && !players.mapmanager.is_enemy_inside(p, x.get()))
					{
						players.mapmanager.move(p, x.get());
						break;
					}
				}

			}
			ac.update_loc(players);
		}
	}


}
*/
void GameManager::complet_action_menu()
{
	Attack action1(view);
	Scheme action2(view);
	action1.update_loc(players);
	int attack = action1.can_attack(players);
	if (attack == 0)
	{

		view.action_menu.action.canAttack = false;
		view.action_menu.action.AttackReason = "ATTACK UNAVAILAVLE-No active cards available for attack";
	}
	else if (attack == 1)
	{
		view.action_menu.action.canAttack = true;
	}
	else if (attack == 2)
	{
		view.action_menu.action.canAttack = false;
		view.action_menu.action.AttackReason = "ATTACK UNAVAILAVLE-No enemy available for attack";
	}
	int scheme = action2.can_scheme(players);
	if (scheme == 2)
	{
		view.action_menu.action.canScheme = false;
		view.action_menu.action.SchemeReason = "SCHEME UNAVAILAVLE-No active cards available for scheme";
	}
	else if (scheme == 1)
	{
		view.action_menu.action.canScheme = true;
	}
	else if (scheme == 0)
	{
		view.action_menu.action.canScheme = false;
		view.action_menu.action.SchemeReason = "SCHEME UNAVAILAVLE-No cards have a living owner for scheme";
	}
}


void GameManager::run()
{
	while (1)
	{
		int mainMenu = view.run_first();
		if (mainMenu == 1)
		{
			try
			{
				vector <int> age = view.run_age();
				vector <int> legend;
				if (age[0] < age[1])
				{
					players.player1.which = 1;
					players.player2.which = 2;
					legend = view.run_legend(1);
				}
				else if (age[0] == age[1])
				{
					Effect e;
					int random = e.rm(1, 2);
					if (random == 1)
					{
						players.player1.which = 1;
						players.player2.which = 2;
						legend = view.run_legend(1);
					}
					else
					{
						players.player1.which = 2;
						players.player2.which = 1;
						legend = view.run_legend(2);
					}
				}
				else
				{
					players.player1.which = 2;
					players.player2.which = 1;
					legend = view.run_legend(2);
				}
				vector <string> photo1;
				vector <string> photo2;
				if (legend[0] == 1)
				{

					players.player1.playerHero = &draculadata;

				}
				else if (legend[0] == 2)
				{
					players.player1.playerHero = &holmesdata;

				}
				else if (legend[0] == 3)
				{
					players.player1.playerHero = &invisiblemandata;
				}
				if (legend[1] == 1)
				{
					players.player2.playerHero = &draculadata;

				}
				else if (legend[1] == 2)
				{
					players.player2.playerHero = &holmesdata;

				}
				else if (legend[1] == 3)
				{
					players.player2.playerHero = &invisiblemandata;
				}
				if (players.player1.which == 1)
				{
					for (auto& x : players.player1.playerHero->heros)
					{
						photo1.emplace_back(x->get_photo());
					}
					for (auto& x : players.player2.playerHero->heros)
					{
						photo2.emplace_back(x->get_photo());
					}
				}
				else
				{
					for (auto& x : players.player1.playerHero->heros)
					{
						photo2.emplace_back(x->get_photo());
					}
					for (auto& x : players.player2.playerHero->heros)
					{
						photo1.emplace_back(x->get_photo());
					}
				}
				view.action_menu.player1 = photo1;
				view.action_menu.player2 = photo2;
				view.action_menu.load_run();
				Action ac(view);
				ac.update_loc(players);
				view.turn = players.player1.which;
				initial_position();
				while (1)
				{
					try
					{

						view.turn = players.player1.which;
						bool exit = false;
						do_at_fisrt();
						ac.update_loc(players);
						if (players.player1.playerHero->heros[0]->get_name() == "DRACULA")
						{
							dracula_ability();
						}
						players.player1.isFoggyFirst = players.mapmanager.is_foggy(players.player1.playerHero->heros[0]->get_position());
						if (players.player1.vanish)
						{
							vector <ActionMenu::cell> allCells = players.mapmanager.all_cells();
							int chosenCell = view.movement1(6, allCells, "", 0);
							players.mapmanager.move(chosenCell, players.player1.playerHero->heros[0].get());
							players.player1.vanish = 0;
						}
						for (int i = 0; i < players.player1.action; i++)
						{
							complet_action_menu();
							int choice;
							while (1)
							{
								int choice1 = view.run_action();
								if (choice1 == 7)
								{
									view.help();
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
								Maneuver maneuver(view);
								maneuver.do_maneuver(players);
								break;
							}
							case 4:
							{
								Scheme scheme(view);
								scheme.do_scheme(players);
								break;
							}

							case 5:
							{
								Attack attack(view);
								attack.do_attack(players);
								break;
							}
							}
							int x = do_at_end();
							if (x != 0)
							{
								exit = true;
								break;
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
						view.text(0, e.what());
					}
				}
			}
			catch (exception& e)
			{
				view.text(0, e.what());
			}
		}
		else if (mainMenu == 2)
		{

		}
		else if (mainMenu == 3)
		{
			break;
		}
	}
}

