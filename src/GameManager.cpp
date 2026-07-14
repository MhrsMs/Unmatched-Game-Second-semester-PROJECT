#include "GameManager.h"
GameManager::GameManager()
{

}
void GameManager::do_at_fisrt(Player& player1, Player& player2)
{
	player1.action = 2;
	player2.action = 2;
	for (auto& x : player1.playerHero->heros)
	{
		x->change_move(0);
	}
	for (auto& x : player2.playerHero->heros)
	{
		x->change_move(0);
	}
	while (!player1.playerHero->heros.front()->is_alive())
	{
		auto hero = move(player1.playerHero->heros.front());
		player1.playerHero->heros.erase(player1.playerHero->heros.begin());
		player1.playerHero->heros.emplace_back(move(hero));
	}
	while (!player2.playerHero->heros.front()->is_alive())
	{
		auto hero = move(player2.playerHero->heros.front());
		player2.playerHero->heros.erase(player2.playerHero->heros.begin());
		player2.playerHero->heros.emplace_back(move(hero));
	}

	while (player1.playerHero->cards.hand.size() > 7)
	{
		vector <string> name;
		int a;
		for (auto x : player1.playerHero->cards.hand)
		{
			name.emplace_back(x.get_cardName());
		}
		a = view.print_complet_needs(6, {}, name);
		player1.playerHero->cards.hand_to_null_card(player1.playerHero->cards.hand[a].get_id());
	}
	while (player2.playerHero->cards.hand.size() > 7)
	{
		vector <string> name;
		int a;
		for (auto x : player2.playerHero->cards.hand)
		{
			name.emplace_back(x.get_cardName());
		}
		a = view.print_complet_needs(6, {}, name);
		player2.playerHero->cards.hand_to_null_card(player2.playerHero->cards.hand[a].get_id());
	}

}
int GameManager::do_at_end(Player& player1, Player& player2)
{
	if (!player1.playerHero->heros[0]->is_alive())
	{
		view.end_of_game(player2.name);
		return 1;
	}
	if (!player2.playerHero->heros[0]->is_alive())
	{
		view.end_of_game(player1.name);
		return 2;
	}
	return 0;
}

void GameManager::maneuver(Player& funplayer1, Player& funplayer2)
{
	if (funplayer1.playerHero->cards.can_deck_to_hand(1))
	{
		funplayer1.playerHero->cards.deck_to_hand(1);
	}
	else
	{
		for (auto& x : funplayer1.playerHero->heros)
		{
			x->decrease_HP(2);
		}
	}
	while (1)
	{
		int m = view.print_maneuver();
		if (m == 1)
		{
			movement(&funplayer1, nullptr);
			break;
		}
		else if (m == 2)
		{
			vector <string> n;
			for (auto& x : funplayer1.playerHero->heros)
			{
				n.emplace_back(x->get_name());
			}
			vector <string> s;
			for (auto x : funplayer1.playerHero->cards.hand)
			{
				s.emplace_back(x.get_cardName());
			}
			vector <int> a = view.print_discarding(s, n);
			int boost = funplayer1.playerHero->cards.hand[a[0]].get_boost();
			int id = funplayer1.playerHero->cards.hand[a[0]].get_id();
			funplayer1.playerHero->cards.hand_to_null_card(id);
			funplayer1.playerHero->heros[a[1]]->change_move(boost);
		}
		else if (m == 3)
		{
			break;
		}
	}


}

void GameManager::scheme(Player& funplayer1, Player& funplayer2)
{
	vector <Card> card;
	bool found = false;
	for (auto x : funplayer1.playerHero->cards.hand)
	{
		if (x.get_kindOfAction() == "Scheme")
		{
			for (auto& y : funplayer1.playerHero->heros)
			{
				if (y->is_alive() && (y->get_name() == x.get_nameOfAttacker() || "Any" == x.get_nameOfAttacker()) && !found)
				{
					card.emplace_back(x);
				}
			}

		}
	}
	if (card.empty())
	{
		throw runtime_error("You don't have any active card");
	}
	vector <string> c;
	for (auto x : card)
	{
		c.emplace_back(x.get_cardName());
	}
	int v = view.print_scheme(c);
	vector <Hero*> team;
	vector <Hero*> target;
	Hero* actor = {};
	for (auto& x : funplayer1.playerHero->heros)
	{
		if (x->get_name() == card[v].get_nameOfAttacker())
		{
			actor = x.get();
		}
		team.emplace_back(x.get());
	}
	for (auto& x : funplayer2.playerHero->heros)
	{
		target.emplace_back(x.get());
	}
	Complet_Needs complet = take_needs(funplayer1, funplayer2, card[v]);
	Data data{ team,target,funplayer1.playerHero->cards,funplayer2.playerHero->cards,mapmanager,*actor };
	Effect effect;
	effect.apply_effect(card[v].get_id(), data, complet);
	if (card[v].get_id() == 2)
	{
		funplayer1.action++;
	}
	if (card[v].get_id() == 16)
	{
		vector <Card> card1;
		for (auto& x : funplayer2.playerHero->cards.hand)
		{
			if (x.get_attackOrDefense() == complet.number)
			{
				card1.emplace_back(x);
			}
		}
		if (card1.empty())
		{
			vector <string> enemy;
			for (auto x : funplayer2.playerHero->cards.hand)
			{
				enemy.emplace_back(x.get_cardName());
			}
			view.show_hand(enemy);
		}
		else
		{
			vector <string> choice;
			for (auto x : card1)
			{
				choice.emplace_back(x.get_cardName());
			}
			int c = view.print_attack2(choice);
			complet.targetPerson->decrease_HP(card[c].get_boost());
		}
	}

}

void GameManager::attack(Player& funplayer1, Player& funplayer2)
{
	vector <Hero*> hero1;
	vector <string> name1;
	for (auto& x : funplayer1.playerHero->heros)
	{
		if (x->is_alive())
		{
			hero1.emplace_back(x.get());
			name1.emplace_back(x->get_name());
		}

	}
	int attacker = view.print_attack1(name1);
	vector <Hero*> hero2;
	vector <string> name2;
	for (auto& x : funplayer2.playerHero->heros)
	{
		if (hero1[attacker]->get_attack_type() == "melee")
		{
			if (mapmanager.is_adjacent(hero1[attacker]->get_position(), x->get_position()) && x->is_alive())
			{
				hero2.emplace_back(x.get());
				name2.emplace_back(x->get_name());
			}
		}
		else
		{
			if (mapmanager.is_same_zone(hero1[attacker]->get_position(), x->get_position()) && x->is_alive())
			{
				hero2.emplace_back(x.get());
				name2.emplace_back(x->get_name());
			}
		}
	}
	if (name2.empty())
	{
		throw runtime_error("There is no available hero");
	}
	view.print_name(funplayer2.name);
	int defender = view.print_attack1(name2);
	vector <Card> card1;
	vector <Card> card2;
	vector <string> c1;
	vector <string> c2;
	for (auto x : funplayer1.playerHero->cards.hand)
	{
		if ((x.get_kindOfAction() == "Attack" || x.get_kindOfAction() == "AttackOrDefense") && (x.get_nameOfAttacker() == name1[attacker] || x.get_nameOfAttacker() == "Any"))
		{
			card1.emplace_back(x);
			c1.emplace_back(x.get_cardName());
		}
	}
	if (c1.empty())
	{
		throw runtime_error("You don't have any active card");
	}
	for (auto x : funplayer2.playerHero->cards.hand)
	{
		if ((x.get_kindOfAction() == "Defense" || x.get_kindOfAction() == "AttackOrDefense") && (x.get_nameOfAttacker() == name2[defender] || x.get_nameOfAttacker() == "Any"))
		{
			card2.emplace_back(x);
			c2.emplace_back(x.get_cardName());
		}
	}
	bool df = 1;
	if (c2.empty())
	{
		df = 0;
	}

	int ca1 = view.print_attack2(c1);
	view.print_name(funplayer2.name);
	int ca2 = view.print_attack2(c2);
	vector <Hero*> target;
	Hero* actor1 = hero1[attacker];
	Hero* actor2 = hero2[defender];
	for (auto& x : funplayer2.playerHero->heros)
	{
		target.emplace_back(x.get());
	}
	Complet_Needs complet1 = take_needs(funplayer1, funplayer2, card1[ca1]);
	Complet_Needs complet2 = take_needs(funplayer1, funplayer2, card2[ca1]);
	Data data1{ hero1,target,funplayer1.playerHero->cards,funplayer2.playerHero->cards,mapmanager,*actor1 };
	Data data2{ target,hero1,funplayer2.playerHero->cards,funplayer1.playerHero->cards,mapmanager,*actor2 };
	Effect effect;
	bool farib1 = 0;
	bool farib2 = 0;
	if (df)
	{
		if (card2[ca2].get_id() == 23 || card2[ca2].get_id() == 10)
		{
			if (card1[ca1].get_nameOfAttacker() == "Any")
			{
				farib2 = 1;
			}

		}
		if (card2[ca2].get_id() == 25)
		{
			if (complet2.number == card1[ca1].get_attackOrDefense())
			{
				farib2 = 1;
			}
		}
	}
	if (card1[ca1].get_id() == 23 || card1[ca1].get_id() == 10)
	{
		if (card2[ca2].get_nameOfAttacker() == "Any")
		{
			farib2 = 1;
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
	if (card1[ca1].get_attackOrDefense() > card2[ca2].get_attackOrDefense())
	{
		complet1.targetPerson->decrease_HP(card1[ca1].get_attackOrDefense() - card2[ca2].get_attackOrDefense());
		if (card1[ca1].get_id() == 24)
		{
			vector <string> fullcard;
			for (auto x : funplayer2.playerHero->cards.hand)
			{
				fullcard.emplace_back(x.get_cardName());
			}
			view.show_hand(fullcard);
		}
		complet1.heroWin = 1;
		complet2.heroWin = 0;
	}
	else if (card1[ca1].get_attackOrDefense() < card2[ca2].get_attackOrDefense())
	{
		complet2.targetPerson->decrease_HP(card2[ca2].get_attackOrDefense() - card1[ca1].get_attackOrDefense());
		if (card2[ca2].get_id() == 24)
		{
			vector <string> fullcard;
			for (auto x : funplayer1.playerHero->cards.hand)
			{
				fullcard.emplace_back(x.get_cardName());
			}
			view.show_hand(fullcard);
		}
		complet1.heroWin = 0;
		complet2.heroWin = 1;
	}
	else
	{
		complet1.heroWin = 0;
		complet2.heroWin = 0;
	}
	if (df)
	{
		if (card2[ca2].get_effectTime() == 3 && !farib1)
		{
			effect.apply_effect(card2[ca2].get_id(), data2, complet2);
		}
	}

	if (card1[ca1].get_effectTime() == 3 && !farib2)
	{
		effect.apply_effect(card1[ca1].get_id(), data1, complet1);
	}
}


Complet_Needs GameManager::take_needs(Player& funplayer1, Player& funplayer2, Card& card)
{
	Complet_Needs complet_needs;
	Needs needs = card.get_Needs();
	if (needs.need_target_person)
	{
		if (card.get_id() == 4)
		{
			vector <Hero*> hero;
			vector <string> name;
			for (auto& x : funplayer2.playerHero->heros)
			{
				hero.emplace_back(x.get());
				name.emplace_back(x->get_name());
			}
			for (auto& x : funplayer1.playerHero->heros)
			{
				hero.emplace_back(x.get());
				name.emplace_back(x->get_name());
			}
			int z = view.print_complet_needs(8, {}, name);
			complet_needs.targetPerson = hero[z];
		}
		else
		{
			vector <string> name;
			for (auto& x : funplayer2.playerHero->heros)
			{
				name.emplace_back(x->get_name());
			}
			int z = view.print_complet_needs(8, {}, name);
			complet_needs.targetPerson = funplayer2.playerHero->heros[z].get();
		}
	}
	if (needs.need_location)
	{
		if (card.get_id() == 1)
		{
			int choice = view.print_complet_needs(1, mapmanager.electable_cells(funplayer1.playerHero->heros[0]->get_position()));
			complet_needs.location = choice;
		}
		if (card.get_id() == 2)
		{
			int cell;
			while (1)
			{
				cell = view.print_complet_needs(2);
				if (!mapmanager.is_ally_inside(cell, funplayer1.playerHero->heros[0].get()), !mapmanager.is_enemy_inside(cell, funplayer1.playerHero->heros[0].get()))
				{
					break;
				}
			}
			complet_needs.location = cell;
		}
		if (card.get_id() == 4)
		{
			view.print_complet_needs(3);
			movement(nullptr, complet_needs.targetPerson, 2, 2);
		}
		if (card.get_id() == 7)
		{
			vector <int> n = mapmanager.electable_cells(complet_needs.targetPerson->get_position());
			int k = view.print_complet_needs(4, n);
			complet_needs.location = n[k];
		}
		if (card.get_id() == 9)
		{
			view.print_complet_needs(5);
			movement(nullptr, complet_needs.teamPerson, 3, 3);
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
			while (1)
			{
				vector <string> cards;
				for (auto x : funplayer1.playerHero->cards.hand)
				{
					cards.emplace_back(x.get_cardName());
				}
				s = view.print_complet_needs(6, {}, cards);
				if (s == 0)
				{
					break;
				}
				optionalcard.emplace_back(funplayer1.playerHero->cards.hand[s - 1]);
			}
			complet_needs.optionalCard = optionalcard;
		}
		if (card.get_id() == 13)
		{
			vector <Card> optionalcard;

			int s;
			while (1)
			{
				vector <string> cards;
				for (auto x : funplayer2.playerHero->cards.hand)
				{
					cards.emplace_back(x.get_cardName());
				}
				s = view.print_complet_needs(6, {}, cards);
				optionalcard.emplace_back(funplayer2.playerHero->cards.hand[s - 1]);
			}
			complet_needs.optionalCard = optionalcard;
		}
	}

	return complet_needs;
}

void GameManager::movement(Player* funplayer1, Hero* hero, int moveMax, int moveMin)
{
	if (hero == nullptr)
	{
		vector <string> s;
		for (auto& x : funplayer1->playerHero->heros)
		{
			s.emplace_back(x->get_name());
		}
		int b = view.print_move_get_name(s);
		hero = funplayer1->playerHero->heros[b].get();
	}

	if (moveMax == 0)
	{
		moveMax = hero->get_move();
	}

	int movementnum = 0;
	int position = hero->get_position();
	while (movementnum <= moveMax)
	{
		vector <int> d = mapmanager.electable_cells(position);
		if (d.empty())
		{
			throw runtime_error("this hero can not move");
		}
		else
		{
			vector <int> a = view.print_move(d);
			if (a[1] == 1)
			{
				if (!mapmanager.is_enemy_inside(a[0], hero))
				{
					position = a[0];
					movementnum++;
				}
			}
			else
			{
				if (!mapmanager.is_enemy_inside(a[0], hero) && !mapmanager.is_ally_inside(a[0], hero) && movementnum >= moveMin)
				{
					mapmanager.move(a[0], hero);
					break;
				}
			}
		}
	}

}

void GameManager::initial_position(Player& funplayer1, Player& funplayer2)
{
	mapmanager.move(22, funplayer1.playerHero->heros[0].get());
	mapmanager.move(9, funplayer2.playerHero->heros[0].get());
	view.print_map(mapmanager.text_inside_cells());
	vector <int> p1;
	vector <int> p2;
	for (auto& x : funplayer1.playerHero->heros)
	{
		if (x->get_position() == 0)
		{
			while (1)
			{
				if (x->get_name() == "SISTER")
				{
					int p = view.print_intitial_position(x->get_name() + " " + x->get_short_name());
					if (mapmanager.is_same_zone(22, p) && !mapmanager.is_ally_inside(p, x.get()) && !mapmanager.is_enemy_inside(p, x.get()))
					{
						mapmanager.move(p, x.get());
						break;
					}
				}
				else
				{
					int p = view.print_intitial_position(x->get_name());
					if (mapmanager.is_same_zone(22, p) && !mapmanager.is_ally_inside(p, x.get()) && !mapmanager.is_enemy_inside(p, x.get()))
					{
						mapmanager.move(p, x.get());
						break;
					}
				}

			}

		}
	}
	for (auto& x : funplayer2.playerHero->heros)
	{
		if (x->get_position() == 0)
		{
			while (1)
			{
				if (x->get_name() == "SISTER")
				{
					int p = view.print_intitial_position(x->get_name() + " " + x->get_short_name());
					if (mapmanager.is_same_zone(9, p) && !mapmanager.is_ally_inside(p, x.get()) && !mapmanager.is_enemy_inside(p, x.get()))
					{
						mapmanager.move(p, x.get());
						break;
					}
				}
				else
				{
					int p = view.print_intitial_position(x->get_name());
					if (mapmanager.is_same_zone(9, p) && !mapmanager.is_ally_inside(p, x.get()) && !mapmanager.is_enemy_inside(p, x.get()))
					{
						mapmanager.move(p, x.get());
						break;
					}
				}

			}

		}
	}

}

ShowActionMenu GameManager::complet_action_menu(Player& funplayer1)
{
	ShowActionMenu show;

	vector <string> nameOfHero;
	vector <int> health;
	vector <int> move;
	vector <int> cell;
	vector <string> text = mapmanager.text_inside_cells();

	vector <string> card;
	vector <string> kind;
	for (auto& x : funplayer1.playerHero->heros)
	{
		nameOfHero.emplace_back(x->get_name());
		health.emplace_back(x->get_HP());
		move.emplace_back(x->get_move());
		cell.emplace_back(x->get_position());
	}
	for (auto x : funplayer1.playerHero->cards.hand)
	{
		card.emplace_back(x.get_cardName());
		kind.emplace_back(x.get_kindOfAction());
	}
	show.name = funplayer1.name;
	show.text = text;
	show.card = card;
	show.cell = cell;
	show.health = health;
	show.kind = kind;
	show.move = move;
	show.nameOfHero = nameOfHero;
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
				Player player1;
				Player player2;
				vector <string> name = view.get_name();
				player1.name = name[0];
				player2.name = name[1];
				if (name[2] == "1")
				{
					player1.playerHero = &draculadata;
					player2.playerHero = &holmesdata;
				}
				else
				{
					player1.playerHero = &holmesdata;
					player2.playerHero = &draculadata;
				}
				initial_position(player1, player2);
				while (1)
				{
					try
					{
						do_at_fisrt(player1, player2);
						for (int i = 0; i < player1.action; i++)
						{
							if (player1.playerHero->heros[0]->get_name() == "DRACULA")
							{
								bool b = view.print_ability();
								if (b)
								{
									vector <Hero*> hero;
									vector <Hero*> hero1;
									vector <string> name;
									for (auto& x : player2.playerHero->heros)
									{
										hero.emplace_back(x.get());
										name.emplace_back(x->get_name());
									}
									for (auto& x : player1.playerHero->heros)
									{
										hero1.emplace_back(x.get());
										hero.emplace_back(x.get());
										name.emplace_back(x->get_name());
									}
									int z = view.print_complet_needs(8, {}, name);
									player1.playerHero->heros[0]->ability(*hero[z], hero1, player1.playerHero->cards);
								}
							}
							int choice = view.print_action_menu(complet_action_menu(player1));
							switch (choice)
							{
							case 1:maneuver(player1, player2); break;
							case 3:scheme(player1, player2); break;
							case 2:attack(player1, player2); break;
							}
							if (choice == 4)
							{
								break;
							}
						}
						for (int i = 0; i < player2.action; i++)
						{
							if (player2.playerHero->heros[0]->get_name() == "DRACULA")
							{
								bool b = view.print_ability();
								if (b)
								{
									vector <Hero*> hero;
									vector <Hero*> hero2;
									vector <string> name;
									for (auto& x : player2.playerHero->heros)
									{
										hero2.emplace_back(x.get());
										hero.emplace_back(x.get());
										name.emplace_back(x->get_name());
									}
									for (auto& x : player1.playerHero->heros)
									{

										hero.emplace_back(x.get());
										name.emplace_back(x->get_name());
									}
									int z = view.print_complet_needs(8, {}, name);
									player2.playerHero->heros[0]->ability(*hero[z], hero2, player2.playerHero->cards);
								}
							}
							int choice = view.print_action_menu(complet_action_menu(player2));
							switch (choice)
							{
							case 1:maneuver(player2, player1); break;
							case 3:scheme(player2, player1); break;
							case 2:attack(player2, player1); break;
							}
							if (choice == 4)
							{
								break;
							}
						}
						int x = do_at_end(player1, player2);
						if (x != 0)
						{
							break;
						}
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

