#include "Scheme.h"
#include "Effect.h"
Scheme::Scheme(Graphics& view) : Action(view)
{
}
void Scheme::do_scheme(PlayerInformation& players)
{
	vector <Card> firstCard = players.player1.playerHero->cards.get_cards_by_action(1);
	vector <Card> secondCard;
	if (players.player1.playerHero->heros[0]->get_name() != "INVISIBLE_MAN")
	{
		if (players.player1.playerHero->heros[1]->is_alive())
		{
			secondCard = firstCard;
		}
		else
		{
			for (auto x : firstCard)
			{
				if (x.get_nameOfDoer() != players.player1.playerHero->heros[1]->get_name())
				{
					secondCard.emplace_back(x);
				}
			}
		}
	}
	else
	{
		secondCard = firstCard;
	}
	update_loc(players);
	int v = view.get_card_action(players.card_to_photo(secondCard));
	view.action_menu.action.thiscard = LoadTexture(secondCard[v].get_cardPhoto().c_str());
	view.action_menu.action.is_thiscard = 1;
	Hero* actor = {};
	for (auto& x : players.unique_to_hero(players.player1))
	{
		if (x->get_name() == secondCard[v].get_nameOfDoer())
		{
			actor = x;
		}
	}
	Complet_Needs complet = take_needs(players, secondCard[v]);
	Data data{ players.unique_to_hero(players.player1),players.unique_to_hero(players.player2),players.player1.playerHero->cards,players.player2.playerHero->cards,players.mapmanager,*actor,&secondCard[v] };
	Effect effect;
	effect.apply_effect(secondCard[v].get_id(), data, complet);
	if (secondCard[v].get_id() == 2 || secondCard[v].get_id() == 35)
	{
		players.player1.action++;
		effect.undo_system_list.back().push_back(make_unique<undo_action>(players));
		if (secondCard[v].get_id() == 35)
		{
			vector <int> foggyCells = players.mapmanager.get_foggy_cells();
			update_loc(players);
			int chosenCell = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells));
			vector <ActionMenu::cell> current_cells = players.mapmanager.all_cells_fog();
			int chosenCell2 = view.movement1(5, current_cells, "", 0);
			players.mapmanager.set_foggy(current_cells[chosenCell2].num, foggyCells[chosenCell]);
			effect.undo_system_list.back().push_back(make_unique<undo_move_fog>(players.mapmanager, current_cells[chosenCell2].num, foggyCells[chosenCell]));
		}
	}
	if (secondCard[v].get_id() == 16)
	{
		vector <Card> card1;
		for (auto x : players.player2.playerHero->cards.hand)
		{
			if (x.get_attackOrDefense() == complet.number)
			{
				card1.emplace_back(x);
			}
		}
		if (card1.empty())
		{
			update_loc(players);
			view.show_hand(players.card_to_photo(players.player2.playerHero->cards.hand));
		}
		else
		{
			view.backCardsSher = 1;
			update_loc(players);
			int c = view.get_card_target(players.card_to_photo(card1));
			complet.targetPerson->decrease_HP(card1[c].get_boost());
			effect.undo_system_list.back().push_back(make_unique<undo_hp>(1, card1[c].get_boost(), complet.targetPerson));
			players.player2.playerHero->cards.hand_to_null_card(card1[c].get_id());
			effect.undo_system_list.back().push_back(make_unique<undo_card>(players.player2.playerHero->cards, 0, c));
			view.backCardsSher = 0;
		}
	}
	if (secondCard[v].get_id() == 37)
	{
		view.backCardsMan = 1;
		vector <int> foggyCells = players.mapmanager.get_foggy_cells();
		update_loc(players);
		int chosenCell = view.get_foggy_cell(players.mapmanager.get_cells(foggyCells));
		movement_fog(players, foggyCells[chosenCell], 2);
		view.backCardsMan = 0;
	}
	if (secondCard[v].get_id() == 38)
	{
		players.player1.playerHero->heros[0]->increase_HP(1);
		effect.undo_system_list.back().push_back(make_unique<undo_hp>(0, 1, players.player1.playerHero->heros[0].get()));
		effect.undo_system_list.back().push_back(make_unique<undo_move_hero>(players.mapmanager, players.player1.playerHero->heros[0]->get_position(), players.player1.playerHero->heros[0].get()));
		players.mapmanager.move(0, players.player1.playerHero->heros[0].get());
		players.player1.vanish = 1;
		players.player1.action = 0;
	}
	players.player1.playerHero->cards.hand_to_null_card(secondCard[v].get_id());
	effect.undo_system_list.back().push_back(make_unique<undo_card>(players.player1.playerHero->cards, 0, v));
	view.action_menu.action.is_thiscard = 0;
}
int Scheme::can_scheme(PlayerInformation& players)
{
	vector <Card> first = players.player1.playerHero->cards.get_cards_by_action(1);
	vector <Card> second;
	if (players.player1.playerHero->heros[0]->get_name() != "INVISIBLE_MAN")
	{
		for (auto x : first)
		{
			if (x.get_nameOfDoer() == players.player1.playerHero->heros[1]->get_name())
			{
				second.emplace_back(x);
			}
		}
	}

	if (first.empty())
	{
		return 2;
	}
	if (players.player1.playerHero->heros[0]->get_name() != "INVISIBLE_MAN")
	{
		if (!players.player1.playerHero->heros[1]->is_alive())
		{
			if (second.size() == first.size())
			{
				return 0;
			}
		}
	}
	return 1;
}


