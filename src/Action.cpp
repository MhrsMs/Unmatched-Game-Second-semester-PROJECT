#include "Action.h"
Action::Action(Graphics& view) : view(view)
{
}
Complet_Needs Action::take_needs(PlayerInformation &players, Card& card, Hero* heroTeam, Hero* heroTarget)
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
			int z = view.get_hero(4,players.hero_to_photo(thishero));
			complet_needs.targetPerson = thishero[z];
		}
		else
		{
			int z = view.get_hero(4, players.hero_to_photo(players.unique_to_hero(players.player2)));
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
						choice = view.movement2(3,"",0);
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
				cell = view.movement2(4, "", 0);
				if (!players.mapmanager.is_ally_inside(cell, players.player1.playerHero->heros[0].get()) && !players.mapmanager.is_enemy_inside(cell, players.player1.playerHero->heros[0].get()))
				{
					break;
				}
			}
			complet_needs.location = cell;
		}
		if (card.get_id() == 4)
		{
			view.text(2);
			movement(players, complet_needs.targetPerson, 2, 2);
		}
		if (card.get_id() == 15)
		{
			vector <int> first = players.mapmanager.electable_cells(players.player1.playerHero->heros[0]->get_position());
			vector <ActionMenu::cell> second;
			for (auto x : first)
			{
				if (!players.mapmanager.is_ally_inside(x, players.player1.playerHero->heros[0].get()))
				{
					ActionMenu::cell i;
					i.num = x;
					i.x = players.mapmanager.get_cell(x)->get_x();
					i.y = players.mapmanager.get_cell(x)->get_y();
					second.emplace_back(i);
				}
			}
			int m = view.movement1(7,second,"",0);
			complet_needs.location = second[m].num;
		}
	}
	if (needs.need_number)
	{
		int s = view.get_number();
		complet_needs.number = s;
	}
	if (needs.need_optional_card)
	{
		vector <Card> optionalcard;
		if (card.get_id() == 8)
		{
			int s;
			bool selected = 0;
			vector <int> c;
			while (1)
			{
				s = view.get_card(1,players.player1.playerHero->cards.hand.size());
				if (s == -2)
				{
					break;
				}
				for (auto x : c)
				{
					if (x == s)
					{
						selected = 1;
						break;
					}
				}
				if (selected)
				{
					continue;
				}
				optionalcard.emplace_back(players.player1.playerHero->cards.hand[s]);
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
					s = view.get_card_target(players.card_to_photo(players.player2.playerHero->cards.hand));
					if (s != -2)
					{
						optionalcard.emplace_back(players.player2.playerHero->cards.hand[s]);
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
		if (card.get_id() == 26)
		{
			for (int i = 0; i < 3; i++)
			{
				if (players.player1.playerHero->cards.can_deck_to_hand(1))
				{
					players.player1.playerHero->cards.deck_to_hand(1);
				}
				else
				{
					players.player1.playerHero->heros[0]->decrease_HP(2);
				}
			}
			for (int i = 0; i < 2; i++)
			{
				int choice = view.get_card(4,players.player1.playerHero->cards.hand.size());
				Card c = players.player1.playerHero->cards.hand[choice];
				players.player1.playerHero->cards.hand.erase(players.player1.playerHero->cards.hand.begin() + choice);
				players.player1.playerHero->cards.deck.emplace_back(c);
			}
		}
		if (card.get_id() == 27)
		{

		}
	}
	return complet_needs;
}

void Action::movement(PlayerInformation &players, Hero* hero, int moveMax, int moveMin)
{
	if (hero == nullptr)
	{
		int b = view.get_hero(3,players.hero_to_photo(players.unique_to_hero(players.player1)));
		hero = players.player1.playerHero->heros[b].get();
		moveMax += hero->get_move();
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
		vector <ActionMenu::cell> d;
		if ((moveMax - movementnum) < 2)
		{
			for (auto x : cell)
			{
				if (!players.mapmanager.is_ally_inside(x, hero))
				{
					ActionMenu::cell c;
					c.num = x;
					c.x = players.mapmanager.get_cell(x)->get_x();
					c.y = players.mapmanager.get_cell(x)->get_y();
					d.emplace_back(c);
				}
			}
		}
		else
		{
			for (auto x : cell)
			{
				ActionMenu::cell c;
				c.num = x;
				c.x = players.mapmanager.get_cell(x)->get_x();
				c.y = players.mapmanager.get_cell(x)->get_y();
				d.emplace_back(c);
			}
		}
		if (d.empty())
		{
			throw runtime_error("this hero can not move");
		}
		else
		{
			int a = view.movement1(2,d,hero->get_name(),moveMax-movementnum);
			if (a == -2)
			{
				if (movementnum < moveMin)
				{
					view.text(4);
				}
				else
				{
					break;
				}
			}
			else
			{
				if (players.mapmanager.is_ally_inside(d[a].num, hero))
				{
					view.text(5);

				}
				else
				{
					players.mapmanager.move(d[a].num, hero);
					update_loc(players);
				}
				movementnum++;
				position = d[a].num;
			}
		}
	}
	update_loc(players);
}

void Action::movement_fog(PlayerInformation& players, int cell, int movementnum)
{
	int move = 0;
	vector <int> cell1 = players.mapmanager.all_adjacent_cells(cell);
	vector <ActionMenu::cell> cell2;
	if (movementnum - move < 2)
	{
		for (auto x : cell1)
		{
			if (!players.mapmanager.is_foggy(x))
			{
				ActionMenu::cell c;
				c.num = x;
				c.x = players.mapmanager.get_cell(x)->get_x();
				c.y = players.mapmanager.get_cell(x)->get_y();
				cell2.emplace_back(c);
			}
		}
	}
	else
	{
		for (auto x : cell1)
		{
			ActionMenu::cell c;
			c.num = x;
			c.x = players.mapmanager.get_cell(x)->get_x();
			c.y = players.mapmanager.get_cell(x)->get_y();
			cell2.emplace_back(c);
		}
	}
	while (move < movementnum)
	{
		int c = view.movement1(5,cell2,"",0);
		if (c == -2)
		{
			break;
		}
		if (players.mapmanager.is_foggy(cell2[c].num))
		{
			view.text(6);
		}
		else
		{
			players.mapmanager.set_foggy(cell2[c].num, cell);
			update_loc(players);
		}
		move++;
		cell = c;
	}
	update_loc(players);
}
void Action::update_loc(PlayerInformation& players)
{
	view.map.clear();
	view.action_menu.action.healthPlayer1.clear();
	view.action_menu.action.healthPlayer2.clear();
	view.action_menu.action.cards.clear();
	for (auto& x : players.player1.playerHero->heros)
	{
		if (x->get_position() != 0)
		{
			ActionMenu::cell cell;
			cell.num = x->get_position();
			cell.heroPhoto = x->get_photo();
			cell.x = players.mapmanager.get_cell(cell.num)->get_x();
			cell.y = players.mapmanager.get_cell(cell.num)->get_y();
			view.map.emplace_back(cell);
		}
	}
	for (auto& x : players.player2.playerHero->heros)
	{
		if (x->get_position() != 0)
		{ 
			ActionMenu::cell cell;
			cell.num = x->get_position();
			cell.heroPhoto = x->get_photo();
			cell.x = players.mapmanager.get_cell(cell.num)->get_x();
			cell.y = players.mapmanager.get_cell(cell.num)->get_y();
			view.map.emplace_back(cell);
		}
	}
	vector <int> fog = players.mapmanager.get_foggy_cells();
	if (!fog.empty())
	{
		for (auto& x : fog)
		{
			ActionMenu::cell cell;
			cell.num = x;
			cell.heroPhoto = "../Assets/fog_cell.png";
			cell.x = players.mapmanager.get_cell(cell.num)->get_x();
			cell.y = players.mapmanager.get_cell(cell.num)->get_y();
			view.map.emplace_back(cell);
		}
	}
	if (players.player1.which == 1)
	{
		for (auto& x : players.player1.playerHero->heros)
		{
			view.action_menu.action.healthPlayer1.emplace_back(x->get_HP());
		}
		for (auto& x : players.player2.playerHero->heros)
		{
			view.action_menu.action.healthPlayer2.emplace_back(x->get_HP());
		}
	}
	else
	{
		for (auto& x : players.player1.playerHero->heros)
		{
			view.action_menu.action.healthPlayer2.emplace_back(x->get_HP());
		}
		for (auto& x : players.player2.playerHero->heros)
		{
			view.action_menu.action.healthPlayer1.emplace_back(x->get_HP());
		}
	}
	for (auto& x : players.player1.playerHero->cards.hand)
	{
		view.action_menu.action.cards.emplace_back(x.get_cardPhoto());
	}
}

