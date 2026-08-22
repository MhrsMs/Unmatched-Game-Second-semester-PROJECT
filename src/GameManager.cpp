#include "GameManager.h"
#include "Effect.h"
void GameManager::do_at_fisrt()
{
	Effect effect;
	Action ac(view);
	view.turn = players.player1.which;
	players.player1.action = 2;
	players.player2.action = 2;
	if (players.player1.playerHero->heros[0]->get_name() == "DRACULA")
	{
		dracula_ability();
	}
	players.player1.isFoggyFirst = players.mapmanager.is_foggy(players.player1.playerHero->heros[0]->get_position());
	if (players.player1.vanish)
	{
		vector <ActionMenu::cell> allCells = players.mapmanager.all_cells();
		ac.update_loc(players);
		int chosenCell = view.movement1(6, allCells, "", 0);
		players.mapmanager.move(allCells[chosenCell].num, players.player1.playerHero->heros[0].get());
		players.player1.vanish = 0;
	}
	effect.undo_system_list.clear();
}

void GameManager::check_every_round()
{
	Action ac(view);
	while (players.player1.playerHero->cards.hand.size() > 7)
	{
		ac.update_loc(players);
		int a = view.get_card(1, players.player1.playerHero->cards.hand.size());
		players.player1.playerHero->cards.hand_to_null_card(players.player1.playerHero->cards.hand[a].get_id());
	}
}

int GameManager::check_every_action()
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
		for (int i = 1; i < n; i++)
		{
			ac.update_loc(players);
			int f = view.movement1(1, same_zone1, "fog", 0);
			if (f >= 0)
			{
				players.mapmanager.set_foggy(same_zone1[f].num);
				same_zone1.erase(same_zone1.begin() + f);
			}
			else
			{
				++n;
			}
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
					ac.update_loc(players);
					int f = view.movement1(1, same_zone1, x->get_name(), 0);
					if (f >= 0)
					{
						players.mapmanager.move(same_zone1[f].num, x.get());
						same_zone1.erase(same_zone1.begin() + f);
						break;
					}

				}
			}
		}
	}
	if (players.player2.playerHero->heros[0]->get_name() == "INVISIBLE_MAN")
	{
		ActionMenu::cell c;
		c.num = 9;
		c.x = players.mapmanager.get_cell(c.num)->get_x();
		c.y = players.mapmanager.get_cell(c.num)->get_y();
		same_zone2.emplace_back(c);
		for (int i = 1; i < n; i++)
		{
			ac.update_loc(players);
			int f = view.movement1(1, same_zone2, "fog", 0);
			if (f >= 0)
			{
				players.mapmanager.set_foggy(same_zone2[f].num);
				same_zone2.erase(same_zone2.begin() + f);
			}
			else
			{
				++n;
			}
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
					ac.update_loc(players);
					int f = view.movement1(1, same_zone2, x->get_name(), 0);
					if (f >= 0)
					{
						players.mapmanager.move(same_zone2[f].num, x.get());
						same_zone2.erase(same_zone2.begin() + f);
						break;
					}

				}
			}
		}
	}
}

void GameManager::complete_action_menu()
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

void GameManager::complete_for_save_game()
{
	Action ac(view);
	ReadInformation ri;
	vector <string> check = ri.ckeck();
	for (auto& x : check)
	{
		cout << x << endl;
		if (x == "0")
		{
			x = " Game not saved yet";
		}
	}
	while (1)
	{
		ac.update_loc(players);
		int c = view.get_save(1, check);
		if (c == -2)
		{
			break;
		}
		int y;
		if (check[c - 1] != " Game not saved yet")
		{
			ac.update_loc(players);
			int y = view.get_save(2, check);
			if (y == 0)
			{
				continue;
			}
		}
		writingData data1;
		data1.effect = players.player1.action;
		data1.which = players.player1.which;
		for (auto& x : players.player1.playerHero->heros)
		{
			string info = x->get_name() + " " + to_string(x->get_HP()) + " " + to_string(x->get_position());
			data1.players_info.emplace_back(info);
		}
		for (auto& x : players.player1.playerHero->cards.hand)
		{
			data1.hand.emplace_back(x.get_id());
		}
		for (auto& x : players.player1.playerHero->cards.null_card)
		{
			data1.null.emplace_back(x.get_id());
		}
		writingData data2;
		data2.effect = players.player2.action;
		data2.which = players.player2.which;
		for (auto& x : players.player2.playerHero->heros)
		{
			string info = x->get_name() + " " + to_string(x->get_HP()) + " " + to_string(x->get_position());
			data2.players_info.emplace_back(info);
		}
		for (auto& x : players.player2.playerHero->cards.hand)
		{
			data2.hand.emplace_back(x.get_id());
		}
		for (auto& x : players.player2.playerHero->cards.null_card)
		{
			data2.null.emplace_back(x.get_id());
		}
		data1.fog.clear();
		data1.fog = players.mapmanager.get_foggy_cells();
		ri.save_data(c, data1, data2);
		break;
	}
}

void GameManager::load_save_game(int which_save)
{
	ReadInformation ri;
	readingData data = ri.read_data(which_save);
	int name1 = 0;
	int	name2 = 0;
	if (data.players_info1[0].name == "DRACULA")
	{
		name1 = 1;
	}
	if (data.players_info1[0].name == "SHERLOCK")
	{
		name1 = 2;
	}
	if (data.players_info1[0].name == "INVISIBLE_MAN")
	{
		name1 = 3;
	}
	if (data.players_info2[0].name == "DRACULA")
	{
		name2 = 1;
	}
	if (data.players_info2[0].name == "SHERLOCK")
	{
		name2 = 2;
	}
	if (data.players_info2[0].name == "INVISIBLE_MAN")
	{
		name2 = 3;
	}
	players.player1.which = data.which1;
	players.player2.which = data.which2;
	players.player1.action = data.effect1;
	players.player2.action = 2;
	match_heros(name1, name2);
	for (int i = 0; i < 5; i++)
	{
		players.player1.playerHero->cards.hand_to_deck_BACK();
		players.player2.playerHero->cards.hand_to_deck_BACK();
	}
	for (int i = 0; i < data.hand1.size(); i++)
	{
		players.player1.playerHero->cards.deck_to_hand_by_id(data.hand1[i]);
	}
	for (int i = 0; i < data.hand2.size(); i++)
	{
		players.player2.playerHero->cards.deck_to_hand_by_id(data.hand2[i]);
	}
	for (int i = 0; i < data.null1.size(); i++)
	{
		players.player1.playerHero->cards.deck_to_null_by_id(data.null1[i]);
	}
	for (int i = 0; i < data.null2.size(); i++)
	{
		players.player2.playerHero->cards.deck_to_null_by_id(data.null2[i]);
	}
	for (int i = 0; i < players.player1.playerHero->heros.size(); i++)
	{
		players.mapmanager.move(data.players_info1[i].position, players.player1.playerHero->heros[i].get());
		players.player1.playerHero->heros[i]->decrease_HP(players.player1.playerHero->heros[i]->get_original_HP() - data.players_info1[i].hp);
	}
	for (int i = 0; i < players.player2.playerHero->heros.size(); i++)
	{
		players.mapmanager.move(data.players_info2[i].position, players.player2.playerHero->heros[i].get());
		players.player2.playerHero->heros[i]->decrease_HP(players.player2.playerHero->heros[i]->get_original_HP() - data.players_info2[i].hp);
	}
	if (players.player1.playerHero->heros[0]->get_name() == "INVISIBLE_MAN" || players.player2.playerHero->heros[0]->get_name() == "INVISIBLE_MAN")
	{
		for (int i = 0; i < 3; i++)
		{
			players.mapmanager.set_foggy(data.fog[i]);
		}
	}
	Action ac(view);
	ac.update_loc(players);
	view.action_menu.load_run();
	view.turn = players.player1.which;
}

void GameManager::match_heros(int nameOfHero1, int nameOfHero2)
{
	vector <string> photo1;
	vector <string> photo2;
	if (nameOfHero1 == 1)
	{

		players.player1.playerHero = &draculadata;

	}
	else if (nameOfHero1 == 2)
	{
		players.player1.playerHero = &holmesdata;

	}
	else if (nameOfHero1 == 3)
	{
		players.player1.playerHero = &invisiblemandata;
	}
	if (nameOfHero2 == 1)
	{
		players.player2.playerHero = &draculadata;

	}
	else if (nameOfHero2 == 2)
	{
		players.player2.playerHero = &holmesdata;

	}
	else if (nameOfHero2 == 3)
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
}

void GameManager::undo()
{
	Effect effect;
	if (!effect.undo_system_list.empty())
	{
		for (int i = effect.undo_system_list.back().size() - 1; i >= 0; i--)
		{
			effect.undo_system_list.back()[i]->undo_function();
		}
		effect.undo_system_list.pop_back();
		++players.player1.action;
	}
}

void GameManager::run_game_action()
{
	bool exit = false;
	Action ac(view);
	while (1)
	{
		try
		{
			do_at_fisrt();
			ac.update_loc(players);
			while (players.player1.action > 0)
			{
				complete_action_menu();
				int choice = view.run_action();
				if (choice == 7)
				{
					view.help();
					continue;
				}
				if (choice == 2)
				{
					undo();
					ac.update_loc(players);
					continue;
				}
				switch (choice)
				{
				case 1:
				{
					exit = true;
					break;
				}
				case 3:
				{
					Effect effect;
					effect.undo_system_list.push_back({});
					Maneuver maneuver(view);
					maneuver.do_maneuver(players);
					--players.player1.action;
					break;
				}
				case 4:
				{
					Effect effect;
					effect.undo_system_list.push_back({});
					Scheme scheme(view);
					scheme.do_scheme(players);
					--players.player1.action;
					break;
				}

				case 5:
				{
					Effect effect;
					effect.undo_system_list.push_back({});
					Attack attack(view);
					attack.do_attack(players);
					--players.player1.action;
					break;
				}
				case 6:
				{
					complete_for_save_game();
					exit = true;
					break;
				}
				}
				int x = check_every_action();
				if (x != 0)
				{
					exit = true;
					break;
				}
				if (exit)
				{
					break;
				}
				if (players.player1.action == 0)
				{
					int turn = view.end_turn();
					if (turn == 1)
					{
						++players.player1.action;
						undo();
					}
				}
			}
			check_every_round();
			PlayerInformation::Player player = players.player1;
			players.player1 = players.player2;
			players.player2 = player;
			if (exit)
			{
				break;
			}
		}
		catch (exception& e)
		{
			view.text(0, e.what());
		}
		if (exit)
		{
			break;
		}
	}
}

void GameManager::run()
{
	bool exit = 0;
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
				match_heros(legend[0], legend[1]);
				view.action_menu.load_run();
				view.turn = players.player1.which;
				Action ac(view);
				ac.update_loc(players);
				initial_position();
				run_game_action();
				exit = 1;
			}
			catch (exception& e)
			{
				view.text(0, e.what());
			}
		}
		if (exit)
		{
			break;
		}
		else if (mainMenu == 2)
		{
			ReadInformation ri;
			vector <string> check = ri.ckeck();
			for (auto& x : check)
			{
				if (x == "0")
				{
					x = " Game not saved yet";
				}
			}
			while (1)
			{
				int c = view.get_save(1, check);
				if (c == -2)
				{
					break;
				}
				if (check[c - 1] == " Game not saved yet")
				{
					continue;
				}
				else
				{
					load_save_game(c);
					run_game_action();
					break;
					exit = 1;
				}
			}
		}
		if (exit)
		{
			break;
		}
		else if (mainMenu == 3)
		{
			break;
		}
	}
}



