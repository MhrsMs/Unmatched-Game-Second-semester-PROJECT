#include "Attack.h"

Attack::Attack(Graphics& view) : Action(view)
{
}
void Attack::do_attack(PlayerInformation& players)
{
	vector <Hero*> hero1 = players.unique_to_hero(players.player1);
	int attacker;
	vector <Hero*> hero2;
	vector <Card> Card1;
	vector <string> photoCard1;
	while (1)
	{
		update_loc(players);
		attacker = view.get_hero(1, players.hero_to_photo(hero1));
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
			update_loc(players);
			view.text(7);
		}
		else
		{
			Card1 = players.player1.playerHero->cards.get_cards_by_action(2, hero1[attacker]);
			if (Card1.empty())
			{
				update_loc(players);
				view.text(8);
			}
			else
			{
				break;
			}
		}
	}
	update_loc(players);
	int defender = view.get_hero(2, players.hero_to_photo(hero2));
	update_loc(players);
	int ca1 = view.get_card_action(players.card_to_photo(Card1));
	view.action_menu.action.thiscard = LoadTexture(Card1[ca1].get_cardPhoto().c_str());
	view.action_menu.action.is_thiscard = 1;
	vector <Card> card2 = players.player2.playerHero->cards.get_cards_by_action(3, hero2[defender]);
	bool df = 1;
	int ca2;
	if (card2.empty())
	{
		df = 0;
	}
	else
	{
		update_loc(players);
		if (players.player1.playerHero->heros[0]->get_name() == "DRACULA")
		{
			view.backCardsDra = 1;
		}
		if (players.player1.playerHero->heros[0]->get_name() == "SHERLOCK")
		{
			view.backCardsSher = 1;
		}
		if (players.player1.playerHero->heros[0]->get_name() == "INVISIBLE_MAN")
		{
			view.backCardsMan = 1;
		}
		ca2 = view.get_card_target(players.card_to_photo(card2));;
		view.backCardsDra = 0;
		view.backCardsMan = 0;
		view.backCardsSher = 0;
		if (ca2 == -2)
		{
			df = 0;
		}
	}
	Complet_Needs complet1 = take_needs(players, Card1[ca1], hero1[attacker], hero2[defender]);
	Complet_Needs complet2;
	Data data1{ hero1,players.unique_to_hero(players.player2),players.player1.playerHero->cards,players.player2.playerHero->cards,players.mapmanager,*hero1[attacker],&Card1[ca1],nullptr };
	Data data2{ players.unique_to_hero(players.player2),hero1,players.player2.playerHero->cards,players.player1.playerHero->cards,players.mapmanager,*hero2[defender],nullptr,&Card1[ca1] };
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
			if (Card1[ca1].get_nameOfDoer() != "SHERLOCK" && Card1[ca1].get_nameOfDoer() != "DR.WATSON")
			{
				farib2 = 1;
			}

		}
		if (card2[ca2].get_id() == 25)
		{
			if (complet2.number == Card1[ca1].get_attackOrDefense())
			{
				farib2 = 1;
				Card1[ca1].change_attackOrDefense(-Card1[ca1].get_attackOrDefense());
			}
		}
	}
	if (Card1[ca1].get_id() == 23 || Card1[ca1].get_id() == 10)
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

	if (Card1[ca1].get_effectTime() == 1 && !farib2)
	{
		effect.apply_effect(Card1[ca1].get_id(), data1, complet1);
	}
	if (df)
	{
		if (card2[ca2].get_effectTime() == 2 && !farib1)
		{
			effect.apply_effect(card2[ca2].get_id(), data2, complet2);
		}
	}

	if (Card1[ca1].get_effectTime() == 2 && !farib2)
	{
		effect.apply_effect(Card1[ca1].get_id(), data1, complet1);

	}
	int defensenumber = 0;
	if (df)
	{
		if (card2[ca2].get_id() == 31)
		{
			Card1[ca1].change_attackOrDefense(-Card1[ca1].get_attackOrDefense());
		}
		if (Card1[ca1].get_id() == 31)
		{
			defensenumber = 0;
		}
		else
		{
			defensenumber = card2[ca2].get_attackOrDefense();
			if (players.mapmanager.is_foggy(players.player2.playerHero->heros[0]->get_position()))
			{
				++defensenumber;
			}
		}
	}

	if (Card1[ca1].get_attackOrDefense() > defensenumber)
	{
		int damage = Card1[ca1].get_attackOrDefense() - defensenumber;
		hero2[defender]->decrease_HP(damage);
		complet1.heroWin = 1;
		if (df)
		{
			complet2.heroWin = 0;
		}
		update_loc(players);
		view.combat(1, damage);
		if (Card1[ca1].get_id() == 24)
		{
			update_loc(players);
			view.show_hand(players.card_to_photo(players.player2.playerHero->cards.hand));
		}
		if (Card1[ca1].get_id() == 7)
		{
			{
				vector <int> first = players.mapmanager.electable_cells(hero2[defender]->get_position());
				vector <ActionMenu::cell> second;
				for (auto& x : first)
				{
					if (!players.mapmanager.is_ally_inside(x, hero2[defender]))
					{
						ActionMenu::cell c;
						c.num = x;
						c.x = players.mapmanager.get_cell(x)->get_x();
						c.y = players.mapmanager.get_cell(x)->get_y();
						second.emplace_back(c);
					}
				}
				update_loc(players);
				int k = view.movement1(4, second, "", 0);
				players.mapmanager.move(second[k].num, players.player1.playerHero->heros[0].get());
			}
		}

	}
	else
	{
		complet1.heroWin = 0;
		if (df)
		{
			complet2.heroWin = 1;
		}
		update_loc(players);
		view.combat(2, 0);
		if (card2[ca2].get_id() == 24)
		{
			update_loc(players);
			view.show_hand(players.card_to_photo(players.player1.playerHero->cards.hand));
		}
	}
	if (df)
	{
		if (players.player1.playerHero->heros[0]->get_name() == "DRACULA")
		{
			view.backCardsDra = 1;
		}
		if (players.player1.playerHero->heros[0]->get_name() == "SHERLOCK")
		{
			view.backCardsSher = 1;
		}
		if (players.player1.playerHero->heros[0]->get_name() == "INVISIBLE_MAN")
		{
			view.backCardsMan = 1;
		}
		if (card2[ca2].get_effectTime() == 3 && !farib1)
		{
			effect.apply_effect(card2[ca2].get_id(), data2, complet2);
			if (players.player1.playerHero->heros[0]->get_name() == "DRACULA")
			{
				view.backCardsDra = 1;
			}
			else if (players.player1.playerHero->heros[0]->get_name() == "SHERLOCK")
			{
				view.backCardsSher = 1;
			}
			else
			{
				view.backCardsMan = 1;
			}
			if (card2[ca2].get_id() == 9)
			{
				if (hero2[defender]->is_alive())
				{
					update_loc(players);
					view.text(3);
					movement(players, hero2[defender], 3, 3);
				}
			}
			if (card2[ca2].get_id() == 26)
			{

				for (int i = 0; i < 3; i++)
				{
					if (players.player2.playerHero->cards.can_deck_to_hand(1))
					{
						players.player2.playerHero->cards.deck_to_hand(1);
					}
					else
					{
						players.player2.playerHero->heros[0]->decrease_HP(2);
					}
				}
				for (int i = 0; i < 2; i++)
				{
					update_loc(players);
					view.text(9);
					int choice = view.get_card_target(players.card_to_photo(players.player2.playerHero->cards.hand));
					Card c = players.player2.playerHero->cards.hand[choice];
					players.player2.playerHero->cards.hand.erase(players.player2.playerHero->cards.hand.begin() + choice);
					players.player2.playerHero->cards.deck.emplace_back(c);
				}

			}
			if (card2[ca2].get_id() == 27)
			{
				view.backCardsMan = 1;
				update_loc(players);
				int yn = view.yes_or_no(2);
				if (yn == 1)
				{
					view.show_hand(players.card_to_photo(players.player1.playerHero->cards.hand));
					int choiceCard = view.get_card_target(players.card_to_photo(players.player1.playerHero->cards.hand));
					players.player1.playerHero->cards.hand_to_null_card(choiceCard);
				}
				else
				{
					view.backCardsMan = 0;
					vector <int> foggyCells = players.mapmanager.get_foggy_cells();
					int chosenCell1 = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells));
					vector <ActionMenu::cell> current_cells = players.mapmanager.all_cells_fog();
					int chosenCell2 = view.movement1(5, current_cells, "", 0);
					players.mapmanager.set_foggy(current_cells[chosenCell2].num, foggyCells[chosenCell1]);
				}
				view.backCardsMan = 0;
			}
			if (card2[ca2].get_id() == 28)
			{
				if (players.player2.playerHero->cards.can_deck_to_hand(1))
				{
					players.player2.playerHero->cards.deck_to_hand(1);
				}
				else
				{
					players.player2.playerHero->heros[0]->decrease_HP(2);
				}
				vector <int> foggyCells1 = players.mapmanager.get_foggy_cells();
				update_loc(players);
				int chosenCell1 = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells1));
				movement_fog(players, foggyCells1[chosenCell1], 2);
				vector <int> foggyCells2 = players.mapmanager.get_foggy_cells();
				int chosenCell2;
				view.backCardsMan = 1;
				update_loc(players);
				chosenCell2 = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells2));
				movement_fog(players, foggyCells2[chosenCell2], 2);
				view.backCardsMan = 0;
			}
			if (card2[ca2].get_id() == 29)
			{
				if (players.mapmanager.is_foggy(players.player2.playerHero->heros[0]->get_position()))
				{
					for (auto& x : players.player1.playerHero->heros)
					{
						if (players.mapmanager.is_foggy(x->get_position()))
						{
							x->decrease_HP(1);
						}
						update_loc(players);
					}
				}
			}
			if (card2[ca2].get_id() == 32)
			{
				if (players.player1.playerHero->heros[0]->get_name() == "DRACULA")
				{
					view.backCardsDra = 1;
				}
				else
				{
					view.backCardsMan = 1;
				}
				movement(players, players.player2.playerHero->heros[0].get(), 1, 1);
				vector <int> foggyCells = players.mapmanager.get_foggy_cells();
				update_loc(players);
				int chosenCell = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells));
				movement_fog(players, foggyCells[chosenCell], 3);
				view.backCardsMan = 0;
				view.backCardsDra = 0;
			}
			if (card2[ca2].get_id() == 33)
			{
				if (players.player2.playerHero->cards.can_deck_to_hand(1))
				{
					players.player2.playerHero->cards.deck_to_hand(1);
				}
				else
				{
					players.player2.playerHero->heros[0]->decrease_HP(2);
				}
				update_loc(players);
				int yn = view.yes_or_no(3);
				if (yn == 1)
				{
					vector <int> foggyCells = players.mapmanager.get_foggy_cells();
					update_loc(players);
					int chosenCell = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells));
					players.mapmanager.move(foggyCells[chosenCell], players.player2.playerHero->heros[0].get());
				}
				else
				{
					vector <int> foggyCells = players.mapmanager.get_foggy_cells();
					update_loc(players);
					int chosenCell = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells));
					movement_fog(players, foggyCells[chosenCell], 3);
				}
			}
		}
		view.backCardsMan = 0;
		view.backCardsDra = 0;
		view.backCardsSher = 0;

	}
	if (Card1[ca1].get_effectTime() == 3 && !farib2)
	{
		effect.apply_effect(Card1[ca1].get_id(), data1, complet1);
		if (Card1[ca1].get_id() == 9 || Card1[ca1].get_id() == 18)
		{
			if (hero1[attacker]->is_alive())
			{
				update_loc(players);
				view.text(3);
				movement(players, hero1[attacker], 3, 3);
			}
		}
		if (Card1[ca1].get_id() == 27)
		{
			view.backCardsMan = 1;
			update_loc(players);
			int yn = view.yes_or_no(2);
			if (yn == 1)
			{
				update_loc(players);
				view.show_hand(players.card_to_photo(players.player2.playerHero->cards.hand));
				int choiceCard = view.get_card_target(players.card_to_photo(players.player2.playerHero->cards.hand));
				players.player2.playerHero->cards.hand_to_null_card(players.player2.playerHero->cards.hand[choiceCard].get_id());
			}
			else
			{
				view.backCardsMan = 0;
				vector <int> foggyCells = players.mapmanager.get_foggy_cells();
				update_loc(players);
				int chosenCell1 = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells));
				vector <ActionMenu::cell> current_cells = players.mapmanager.all_cells_fog();
				int chosenCell2 = view.movement1(5, current_cells, "", 0);
				players.mapmanager.set_foggy(current_cells[chosenCell2].num, foggyCells[chosenCell1]);
			}
			view.backCardsMan = 0;
		}
		if (Card1[ca1].get_id() == 28)
		{
			if (players.player1.playerHero->cards.can_deck_to_hand(1))
			{
				players.player1.playerHero->cards.deck_to_hand(1);
			}
			else
			{
				players.player1.playerHero->heros[0]->decrease_HP(2);
			}
			vector <int> foggyCells1 = players.mapmanager.get_foggy_cells();
			update_loc(players);
			int chosenCell1 = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells1));
			movement_fog(players, foggyCells1[chosenCell1], 2);
			vector <int> foggyCells2 = players.mapmanager.get_foggy_cells();
			view.backCardsMan = 1;
			int chosenCell2;
			update_loc(players);
			chosenCell2 = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells2));
			movement_fog(players, foggyCells2[chosenCell2], 2);
			view.backCardsMan = 0;
		}
		if (Card1[ca1].get_id() == 29)
		{
			if (players.mapmanager.is_foggy(players.player1.playerHero->heros[0]->get_position()))
			{
				for (auto& x : players.player2.playerHero->heros)
				{
					if (players.mapmanager.is_foggy(x->get_position()))
					{
						x->decrease_HP(1);
					}
					update_loc(players);
				}
			}
		}
		if (Card1[ca1].get_id() == 36)
		{
			vector <int> foggyCells = players.mapmanager.get_foggy_cells();
			update_loc(players);
			int chosenCell1 = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells));
			vector <ActionMenu::cell> current_cells = players.mapmanager.all_cells_fog();
			for (int i = 0; i < current_cells.size();)
			{
				if (players.mapmanager.get_cell(current_cells[i].num)->get_hero_inside() != nullptr)
				{
					current_cells.erase(current_cells.begin() + i);
				}
				else
				{
					++i;
				}
			}
			update_loc(players);
			int chosenCell2 = view.movement1(5, current_cells, "", 0);
			players.mapmanager.set_foggy(current_cells[chosenCell2].num, foggyCells[chosenCell1]);
			players.mapmanager.move(current_cells[chosenCell2].num, players.player1.playerHero->heros[0].get());
		}

	}
	players.player1.playerHero->cards.hand_to_null_card(Card1[ca1].get_id());
	if (df)
	{
		players.player2.playerHero->cards.hand_to_null_card(card2[ca2].get_id());
	}

	view.action_menu.action.is_thiscard = 0;
	update_loc(players);
}
int Attack::can_attack(PlayerInformation& players)
{
	vector <Card> mainhero = players.player1.playerHero->cards.get_cards_by_action(2, players.player1.playerHero->heros[0].get());
	vector <Card> otherhero;
	vector <Hero*> hero;
	if (players.player1.playerHero->heros[0]->get_name() != "INVISIBLE_MAN")
	{
		if (players.player1.playerHero->heros[1]->is_alive())
		{
			otherhero = players.player1.playerHero->cards.get_cards_by_action(2, players.player1.playerHero->heros[1].get());
		}
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

