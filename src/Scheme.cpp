#include "Scheme.h"
void Scheme::do_scheme(PlayerInformation& players)
{
	vector <Card> firstCard = players.player1.playerHero->cards.get_cards_by_action(1);
	vector <Card> secondCard;
	bool found = false;
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

	int v = view.print_scheme(players.card_to_name(secondCard));
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
	if (secondCard[v].get_id() == 2)
	{
		players.player1.action++;
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
			view.show_hand(players.card_to_name(players.player2.playerHero->cards.hand));
		}
		else
		{
			int c = view.print_attack2(players.card_to_name(card1), 3);
			complet.targetPerson->decrease_HP(card1[c].get_boost());
		}
	}
	players.player1.playerHero->cards.hand_to_null_card(secondCard[v].get_id());
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


