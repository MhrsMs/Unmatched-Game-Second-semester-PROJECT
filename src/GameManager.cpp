#include "GameManager.h"
vector<string> GameManager::hero_to_name(vector <Hero*> hero)
{
	vector <string> s;
	for (auto x : hero)
	{
		if (x->get_name() == "SISTER")
		{
			s.emplace_back(x->get_name() + " " + x->get_short_name());
		}
		else
		{
			s.emplace_back(x->get_name());
		}
	}
	return s;
}

vector<string> GameManager::card_to_name(vector<Card> card)
{
	vector <string> s;
	for (auto x : card)
	{
		s.emplace_back(x.get_cardName());
	}
	return s;
}

vector<Hero*> GameManager::unique_to_hero(Player player)
{
	vector <Hero*> hero;
	for (auto& x : player.playerHero->heros)
	{
		if (x->is_alive())
		{
			hero.emplace_back(x.get());
		}
	}
	return hero;
}

void GameManager::do_at_fisrt(Player& player1, Player& player2)
{
	player1.action = 2;
	player2.action = 2;
	while (player1.playerHero->cards.hand.size() > 7)
	{
		int a = view.print_discarding(card_to_name(player1.playerHero->cards.hand));
		player1.playerHero->cards.hand_to_null_card(player1.playerHero->cards.hand[a - 1].get_id());
	}
	while (player2.playerHero->cards.hand.size() > 7)
	{
		int a = view.print_discarding(card_to_name(player2.playerHero->cards.hand));
		player2.playerHero->cards.hand_to_null_card(player2.playerHero->cards.hand[a - 1].get_id());
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
	auto& heros1 = player1.playerHero->heros;
	stable_partition(heros1.begin() + 1, heros1.end(), [](const auto& hero)
		{
			return hero && hero->is_alive();
		});
	auto& heros2 = player2.playerHero->heros;
	stable_partition(heros2.begin() + 1, heros2.end(), [](const auto& hero)
		{
			return hero && hero->is_alive();
		});
	return 0;
}

void GameManager::maneuver(Player& player1, Player& player2)
{
	if (player1.playerHero->cards.can_deck_to_hand(1))
	{
		player1.playerHero->cards.deck_to_hand(1);
		view.print_hand_cards(card_to_name(player1.playerHero->cards.hand));
	}
	else
	{
		for (auto& x : player1.playerHero->heros)
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
			movement(&player1, nullptr, boost);
			break;
		}
		else if (m == 2)
		{
			int a = view.print_discarding(card_to_name(player1.playerHero->cards.hand));
			if (a == 0)
			{
				continue;
			}
			boost = boost + player1.playerHero->cards.hand[a - 1].get_boost();
			int id = player1.playerHero->cards.hand[a - 1].get_id();
			player1.playerHero->cards.hand_to_null_card(id);
		}
		else if (m == 3)
		{
			break;
		}
	}
}

void GameManager::scheme(Player& player1, Player& player2)
{
	vector <Card> firstCard = player1.playerHero->cards.get_cards_by_action(1);
	vector <Card> secondCard;
	bool found = false;
	if (player1.playerHero->heros[1]->is_alive())
	{
		secondCard = firstCard;
	}
	else
	{
		for (auto x : firstCard)
		{
			if (x.get_nameOfDoer() != player1.playerHero->heros[1]->get_name())
			{
				secondCard.emplace_back(x);
			}
		}
	}
	int v = view.print_scheme(card_to_name(secondCard));
	Hero* actor = {};
	for (auto& x : unique_to_hero(player1))
	{
		if (x->get_name() == secondCard[v].get_nameOfDoer())
		{
			actor = x;
		}
	}
	Complet_Needs complet = take_needs(player1, player2, secondCard[v]);
	Data data{ unique_to_hero(player1),unique_to_hero(player2),player1.playerHero->cards,player2.playerHero->cards,mapmanager,*actor,&secondCard[v] };
	Effect effect;
	effect.apply_effect(secondCard[v].get_id(), data, complet);
	if (secondCard[v].get_id() == 2)
	{
		player1.action++;
	}
	if (secondCard[v].get_id() == 16)
	{
		vector <Card> card1;
		for (auto x : player2.playerHero->cards.hand)
		{
			if (x.get_attackOrDefense() == complet.number)
			{
				card1.emplace_back(x);
			}
		}
		if (card1.empty())
		{
			view.show_hand(card_to_name(player2.playerHero->cards.hand));
		}
		else
		{
			int c = view.print_attack2(card_to_name(card1), 3);
			complet.targetPerson->decrease_HP(card1[c].get_boost());
		}
	}
	player1.playerHero->cards.hand_to_null_card(secondCard[v].get_id());
}

void GameManager::attack(Player& player1, Player& player2)
{
	vector <Hero*> hero1 = unique_to_hero(player1);
	int attacker;
	vector <Hero*> hero2;
	vector <Card> card1;
	while (1)
	{
		attacker = view.print_attack1(hero_to_name(hero1), 1);
		for (auto& x : player2.playerHero->heros)
		{
			if (x->is_alive())
			{
				if (hero1[attacker]->get_attack_type() == "melee")
				{
					if (mapmanager.is_adjacent(hero1[attacker]->get_position(), x->get_position()))
					{

						hero2.emplace_back(x.get());
					}
				}
				else
				{
					if (mapmanager.is_same_zone(hero1[attacker]->get_position(), x->get_position()) || mapmanager.is_adjacent(hero1[attacker]->get_position(), x->get_position()))
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
			card1 = player1.playerHero->cards.get_cards_by_action(2, hero1[attacker]);
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
	int defender = view.print_attack1(hero_to_name(hero2), 2);
	int ca1 = view.print_attack2(card_to_name(card1), 1);
	vector <Card> card2 = player2.playerHero->cards.get_cards_by_action(3, hero2[defender]);
	bool df = 1;
	int ca2;
	if (card2.empty())
	{
		df = 0;
	}
	else
	{
		view.print_name(player2.name);
		ca2 = view.print_attack2(card_to_name(card2), 2);
		if (ca2 == 0)
		{
			df = 0;
		}
		else
		{
			ca2 = ca2 - 1;
		}
	}
	Complet_Needs complet1 = take_needs(player1, player2, card1[ca1], hero1[attacker], hero2[defender]);
	Complet_Needs complet2;
	Data data1{ hero1,unique_to_hero(player2),player1.playerHero->cards,player2.playerHero->cards,mapmanager,*hero1[attacker],&card1[ca1],nullptr };
	Data data2{ unique_to_hero(player2),hero1,player2.playerHero->cards,player1.playerHero->cards,mapmanager,*hero2[defender],nullptr,&card1[ca1] };
	if (df)
	{
		complet2 = take_needs(player2, player1, card2[ca2], hero2[defender], hero1[attacker]);
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
			if (card1[ca1].get_nameOfDoer() == "Any" || card1[ca1].get_nameOfDoer() == "DRAUCLA" || card1[ca1].get_nameOfDoer() == "SISTER")
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
			if (card2[ca2].get_nameOfDoer() == "Any" || card2[ca2].get_nameOfDoer() == "SISTER" || card2[ca2].get_nameOfDoer() == "DRACULA")
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
			view.show_hand(card_to_name(player2.playerHero->cards.hand));
		}
		complet1.heroWin = 1;
		if (df)
		{
			complet2.heroWin = 0;
		}
		if (card1[ca1].get_id() == 7)
		{
			{
				vector <int> first = mapmanager.electable_cells(hero2[defender]->get_position());
				vector <int> second;
				for (auto x : first)
				{
					if (!mapmanager.is_ally_inside(x, hero2[defender]))
					{
						second.emplace_back(x);
					}
				}
				int k = view.print_complet_needs(4, second);
				mapmanager.move(second[k], player1.playerHero->heros[0].get());
			}
		}
		view.print_combat_result(1, damage);
	}

	else
	{
		if (card2[ca2].get_id() == 24)
		{
			view.show_hand(card_to_name(player1.playerHero->cards.hand));
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
					movement(nullptr, hero2[defender], 3, 3);
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
				movement(nullptr, hero1[attacker], 3, 3);
			}
		}

	}
	player1.playerHero->cards.hand_to_null_card(card1[ca1].get_id());
	if (df)
	{
		player2.playerHero->cards.hand_to_null_card(card2[ca2].get_id());
	}
}

void GameManager::dracula_ability(Player& player1)
{
	view.print_map(mapmanager.text_inside_cells());
	bool b = view.print_ability(1);
	if (b)
	{
		vector <Hero*> hero = mapmanager.nearby_heroes(player1.playerHero->heros[0]->get_position());
		if (!hero.empty())
		{
			vector <Hero*> hero1;
			for (auto& x : player1.playerHero->heros)
			{
				hero1.emplace_back(x.get());
			}
			int z = view.print_complet_needs(8, {}, hero_to_name(hero));
			player1.playerHero->heros[0]->ability(*hero[z], hero1, player1.playerHero->cards);
		}
		else
		{
			view.print_ability(2);
		}
	}
}

Complet_Needs GameManager::take_needs(Player& player1, Player& player2, Card& card, Hero* heroTeam, Hero* heroTarget)
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
			for (auto& x : player2.playerHero->heros)
			{
				thishero.emplace_back(x.get());
			}
			for (auto& x : player1.playerHero->heros)
			{
				thishero.emplace_back(x.get());
			}
			int z = view.print_complet_needs(8, {}, hero_to_name(thishero));
			complet_needs.targetPerson = thishero[z];
		}
		else
		{
			int z = view.print_complet_needs(8, {}, hero_to_name(unique_to_hero(player2)));
			complet_needs.targetPerson = player2.playerHero->heros[z].get();
		}

	}
	if (needs.need_location)
	{
		if (card.get_id() == 1)
		{
			bool dead = false;
			for (auto& x : player1.playerHero->heros)
			{
				if (x->get_name() == "SISTER" && !x->is_alive())
				{
					dead = true;
					int choice;
					while (1)
					{
						choice = view.print_complet_needs(1);
						if (mapmanager.is_same_zone(player1.playerHero->heros[0]->get_position(), choice))
						{
							break;
						}
					}
					player1.playerHero->heros[0]->increase_HP(2);
					x->increase_HP(x->get_original_HP());
					mapmanager.move(choice, x.get());
				}
			}
		}
		if (card.get_id() == 2)
		{
			int cell;
			while (1)
			{
				cell = view.print_complet_needs(2);
				if (!mapmanager.is_ally_inside(cell, player1.playerHero->heros[0].get()) && !mapmanager.is_enemy_inside(cell, player1.playerHero->heros[0].get()))
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
		if (card.get_id() == 15)
		{
			vector <int> first = mapmanager.electable_cells(player1.playerHero->heros[0]->get_position());
			vector <int> second;
			for (auto x : first)
			{
				if (!mapmanager.is_ally_inside(x, player1.playerHero->heros[0].get()))
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
			for (auto x : player1.playerHero->cards.hand)
			{
				if (x.get_cardName() != card.get_cardName())
				{
					cards.emplace_back(x);
				}
			}
			while (1)
			{
				s = view.print_discarding(card_to_name(player1.playerHero->cards.hand));
				if (s == 0)
				{
					break;
				}
				optionalcard.emplace_back(cards[s - 1]);
			}
			complet_needs.optionalCard = optionalcard;
		}
		if (card.get_id() == 13)
		{
			vector <Card> optionalcard;
			int s;
			while (1)
			{
				if (!player1.playerHero->cards.hand.empty())
				{
					s = view.print_discarding(card_to_name(player2.playerHero->cards.hand));
					if (s != 0)
					{
						optionalcard.emplace_back(player2.playerHero->cards.hand[s - 1]);
						break;
					}
				}
			}
			complet_needs.optionalCard = optionalcard;
		}
	}
	return complet_needs;
}

void GameManager::movement(Player* player1, Hero* hero, int moveMax, int moveMin)
{
	if (hero == nullptr)
	{
		int b = view.print_move_get_name(hero_to_name(unique_to_hero(*player1)));
		hero = player1->playerHero->heros[b].get();
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
		vector <int> cell = mapmanager.electable_cells(position);
		vector <int> d;
		if ((moveMax - movementnum) < 2)
		{
			for (auto x : cell)
			{
				if (!mapmanager.is_ally_inside(x, hero))
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
				if (mapmanager.is_ally_inside(d[a - 1], hero))
				{
					view.print_move2(1);

				}
				else
				{
					mapmanager.move(d[a - 1], hero);
					view.print_map(mapmanager.text_inside_cells());
				}
				movementnum++;
				position = d[a - 1];
			}
		}
	}
}

void GameManager::initial_position(Player& player1, Player& player2)
{
	mapmanager.move(22, player1.playerHero->heros[0].get());
	mapmanager.move(9, player2.playerHero->heros[0].get());
	view.print_map(mapmanager.text_inside_cells());

	vector <int> p1;
	vector <int> p2;
	for (auto& x : player1.playerHero->heros)
	{
		if (x->get_position() == 0)
		{
			while (1)
			{
				if (x->get_name() == "SISTER")
				{
					int p = view.print_initial_position(x->get_name() + " " + x->get_short_name());
					if (mapmanager.is_same_zone(22, p) && !mapmanager.is_ally_inside(p, x.get()) && !mapmanager.is_enemy_inside(p, x.get()))
					{
						mapmanager.move(p, x.get());
						break;
					}
				}
				else
				{
					int p = view.print_initial_position(x->get_name());
					if (mapmanager.is_same_zone(22, p) && !mapmanager.is_ally_inside(p, x.get()) && !mapmanager.is_enemy_inside(p, x.get()))
					{
						mapmanager.move(p, x.get());
						break;
					}
				}

			}

		}
	}
	for (auto& x : player2.playerHero->heros)
	{
		if (x->get_position() == 0)
		{
			while (1)
			{
				if (x->get_name() == "SISTER")
				{
					int p = view.print_initial_position(x->get_name() + " " + x->get_short_name());
					if (mapmanager.is_same_zone(9, p) && !mapmanager.is_ally_inside(p, x.get()) && !mapmanager.is_enemy_inside(p, x.get()))
					{
						mapmanager.move(p, x.get());
						break;
					}
				}
				else
				{
					int p = view.print_initial_position(x->get_name());
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

ShowActionMenu GameManager::complet_action_menu(Player& player1, Player& player2)
{
	ShowActionMenu show;
	int attack = can_attack(player1, player2);
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
	int scheme = can_scheme(player1, player2);
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
	for (auto& x : player1.playerHero->heros)
	{
		show.nameOfHero.emplace_back(x->get_name());
		show.health.emplace_back(x->get_HP());
		show.move.emplace_back(x->get_move());
		show.cell.emplace_back(x->get_position());
	}
	for (auto x : player1.playerHero->cards.hand)
	{
		show.card.emplace_back(x.get_cardName());
		show.kind.emplace_back(x.get_kindOfAction());
		show.nameOfDoer.emplace_back(x.get_nameOfDoer());
	}
	for (auto& x : player2.playerHero->heros)
	{
		show.nameofEnemy.emplace_back(x->get_name());
		show.healthEnemy.emplace_back(x->get_HP());
	}

	show.name = player1.name;
	show.text = mapmanager.text_inside_cells();;
	return show;
}

int GameManager::can_scheme(Player& player1, Player& player2)
{
	vector <Card> first = player1.playerHero->cards.get_cards_by_action(1);
	vector <Card> second;
	for (auto x : first)
	{
		if (x.get_nameOfDoer() == player1.playerHero->heros[1]->get_name())
		{
			second.emplace_back(x);
		}
	}
	if (first.empty())
	{
		return 2;
	}
	if (!player1.playerHero->heros[1]->is_alive())
	{
		if (second.size() == first.size())
		{
			return 0;
		}
	}
	return 1;
}

int GameManager::can_attack(Player& player1, Player& player2)
{
	vector <Card> mainhero = player1.playerHero->cards.get_cards_by_action(2, player1.playerHero->heros[0].get());
	vector <Card> otherhero;
	vector <Hero*> hero;
	if (player1.playerHero->heros[1]->is_alive())
	{
		otherhero = player1.playerHero->cards.get_cards_by_action(2, player1.playerHero->heros[1].get());
	}
	if (mainhero.empty() || otherhero.empty())
	{
		return 0;
	}

	bool found = false;
	for (int i = 0; i < player1.playerHero->heros.size() && !found; i++)
	{
		if (player1.playerHero->heros[i]->is_alive())
		{
			if (player1.playerHero->heros[i]->get_attack_type() == "melee")
			{
				for (auto& x : player2.playerHero->heros)
				{
					if (x->is_alive())
					{
						if (mapmanager.is_adjacent(x->get_position(), player1.playerHero->heros[i]->get_position()))
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
				for (auto& x : player2.playerHero->heros)
				{
					if (x->is_alive())
					{
						if (mapmanager.is_same_zone(x->get_position(), player1.playerHero->heros[i]->get_position()) || mapmanager.is_adjacent(x->get_position(), player1.playerHero->heros[i]->get_position()))
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
						bool exit = false;
						do_at_fisrt(player1, player2);
						if (player1.playerHero->heros[0]->get_name() == "DRACULA")
						{
							dracula_ability(player1);
						}
						for (int i = 0; i < player1.action; i++)
						{
							int choice;
							while (1)
							{
								int choice1 = view.print_action_menu(complet_action_menu(player1, player2));
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
							case 3:maneuver(player1, player2); break;
							case 4:scheme(player1, player2); break;
							case 5:attack(player1, player2); break;
							}
							int x = do_at_end(player1, player2);
							if (x != 0)
							{
								break;
							}

						}
						if (exit)
						{
							break;
						}
						Player player = player1;
						player1 = player2;
						player2 = player;
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

