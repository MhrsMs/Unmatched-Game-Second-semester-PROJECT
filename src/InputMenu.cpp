#include "InputMenu.h"
#include "InputNumber.h"
#include <iostream>
using namespace std;
void InputMenu::load_movement()
{
	cell = LoadTexture("../Assets/cell.png");
	button = LoadTexture("../Assets/button_action.png");
}

void InputMenu::draw_movement(int a, std::vector <ActionMenu::cell>& map, std::string name, int move)
{
	for (int i = 0; i < map.size(); i++)
	{
		DrawTexturePro(cell, { 0,0,(float)cell.width,(float)cell.height }, { map[i].x - 7,map[i].y - 5,80,80 }, { 0,0 }, 0, WHITE);
	}
	string text;
	Rectangle r;
	Rectangle b;
	switch (a)
	{
	case 1:
	{
		text = "Select the initial position of : " + name; break;
	}
	case 2:
	{
		text = "Allowed moves : " + to_string(move) + " Which house are you going to?"; break;
	}
	case 3:
	{
		text = "Select the cell where you want \nsister to return :"; break;
	}
	case 4:
	{
		text = "Select the cell where you want\n Dracula to be placed:"; break;
	}
	case 5:
	{
		text = "Select the cell where you want\n fog to be placed:"; break;
	}
	case 6:
	{
		text = "Select the cell where you want\n Invisible_men to be placed:"; break;
	}
	case 7:
	{
		text = "Select the cell where you want\n Dr.Watson to be placed:"; break;
	}
	default:
	{
		text = " "; break;
	}
	}

	if (a == 1 || a == 2)
	{
		r = { 857,669 ,665,176 };
	}
	else
	{
		r = { 1050,673,507,172 };
	}
	if (a == 2 || a == 5)
	{
		r.y = r.y - 15;
		b = { 1109,790,165,48 };
		Vector2 t1 = MeasureTextEx(font, "NONE", 20, 2);
		DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, b, { 0,0 }, 0, WHITE);
		DrawTextEx(font, "NONE", { b.x + (b.width - t1.x) / 2,b.y + (b.height - t1.y) / 2 }, 20, 2, WHITE);
	}
	Vector2 t = MeasureTextEx(font, text.c_str(), 30, 2);
	DrawTextEx(font, text.c_str(), { r.x + (r.width - t.x) / 2,r.y + (r.height - t.y) / 2 }, 30, 2, WHITE);

}

void InputMenu::unload_movement()
{
	UnloadTexture(cell);
	UnloadTexture(button);
}

int InputMenu::check_movement(std::vector <ActionMenu::cell>& map)
{
	Vector2 mouse = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		for (int i = 0; i < map.size(); i++)
		{
			if (CheckCollisionPointRec(mouse, { map[i].x - 5,map[i].y - 7,80,80 }))
			{
				return i;
			}
		}
		if (CheckCollisionPointRec(mouse, { 1109,777,165,48 }))
		{
			return -2;
		}
	}
	return -1;
}

void InputMenu::load_maneuver()
{
	button = LoadTexture("../Assets/button_action.png");
}

void InputMenu::unload_maneuver()
{
	UnloadTexture(button);
}

void InputMenu::draw_maneuver()
{
	DrawTextEx(font, "MANEUVER", { 1100,690 }, 30, 2, WHITE);
	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 859,742,225,66 }, { 0,0 }, 0, WHITE);
	Vector2 t1 = MeasureTextEx(font, "MOVE", 25, 2);
	DrawTextEx(font, "MOVE", { 859 + (225 - t1.x) / 2,742 + (66 - t1.y) / 2 }, 25, 2, WHITE);

	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 1084,742,225,66 }, { 0,0 }, 0, WHITE);
	Vector2 t2 = MeasureTextEx(font, "DISCARDING", 25, 2);
	DrawTextEx(font, "DISCARDING", { 1084 + (225 - t2.x) / 2,742 + (66 - t2.y) / 2 }, 25, 2, WHITE);

	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 1309,742,225,66 }, { 0,0 }, 0, WHITE);
	Vector2 t3 = MeasureTextEx(font, "NONE", 25, 2);
	DrawTextEx(font, "NONE", { 1309 + (225 - t3.x) / 2,742 + (66 - t3.y) / 2 }, 25, 2, WHITE);
}

int InputMenu::check_maneuver()
{
	Vector2 mouse = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (CheckCollisionPointRec(mouse, { 859,742,225,66 }))
		{
			return 1;
		}
		else if (CheckCollisionPointRec(mouse, { 1084,742,225,66 }))
		{
			return 2;
		}
		else if (CheckCollisionPointRec(mouse, { 1309,742,225,66 }))
		{
			return 3;
		}
	}
	return -1;
}

void InputMenu::load_card()
{
	divider = LoadTexture("../Assets/divider.png");

}

void InputMenu::draw_card(Texture2D& card)
{
	DrawTexturePro(card, { 0,0,(float)card.width,(float)card.height }, { 856,684,115,161 }, { 0,0 }, 0, WHITE);
	DrawTexturePro(divider, { 0,0,(float)divider.width,(float)divider.height }, { 971,669,44,191 }, { 0,0 }, 0, WHITE);
}

void InputMenu::unload_card()
{
	UnloadTexture(divider);
}

std::vector<Texture2D> InputMenu::load_hero(const std::vector<std::string>& hero)
{
	std::vector<Texture2D> result;
	for (auto& x : hero)
	{
		result.emplace_back(LoadTexture(x.c_str()));
	}
	return result;
}

void InputMenu::unload_hero(std::vector<Texture2D>& hero)
{
	for (auto& x : hero)
	{
		UnloadTexture(x);
	}
}

void InputMenu::draw_hero(int a, std::vector<Texture2D>& hero)
{
	if (!hero.empty())
	{
		int x = 390 / hero.size();
		for (int i = 0; i < hero.size(); i++)
		{
			DrawTexturePro(hero[i], { 0,0,(float)hero[i].width,(float)hero[i].height }, { 1026 + float(i * x),739,91,91 }, { 0,0 }, 0, WHITE);
		}
		string text;
		switch (a)
		{
		case 1:
		{
			text = "which hero do you want to fight with?"; break;
		}
		case 2:
		{
			text = "which hero do you want to attack?"; break;
		}
		case 3:
		{
			text = "which hero do you want to move?"; break;
		}
		case 4:
		{
			text = "which hero do you want to target?"; break;
		}
		default:
		{
			text = " "; break;
		}
		}

		DrawTextEx(font, text.c_str(), { 1022,683 }, 25, 2, WHITE);
	}
}

int InputMenu::check_hero(int hero)
{
	if (hero != 0)
	{
		int x = 390 / hero;
		Vector2 mouse = GetMousePosition();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			for (int i = 0; i < hero; i++)
			{
				if (CheckCollisionPointRec(mouse, { 1026 + (float)(i * x),739,91,91 }))
				{
					return i;
				}
			}

		}
	}

	return -1;
}

int InputMenu::check_cards(int a, int cards)
{

	if (a == 1)
	{
		if (cards != 0)
		{
			int x = 570 / cards;
			Vector2 mouse = GetMousePosition();
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				for (int i = 0; i < cards; i++)
				{
					if (CheckCollisionPointRec(mouse, { (float)70 + (i * x), 677, 115, 160 }))
					{
						return i;
					}
				}
				if (CheckCollisionPointRec(mouse, { 1109, 777, 165, 48 }))
				{
					return -2;
				}
			}
		}

	}
	else
	{
		if (cards != 0)
		{
			int x = 390 / cards;
			Vector2 mouse = GetMousePosition();
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				for (int i = 0; i < cards; i++)
				{
					if (CheckCollisionPointRec(mouse, { 1026 + (float)(i * x), 718, 91, 127 }))
					{
						return i;
					}
				}
				return -2;
			}
		}

	}
	return -1;
}

void InputMenu::draw_hand(std::vector<Texture2D>& cards)
{
	if (!cards.empty())
	{
		int x = 390 / cards.size();
		for (int i = 0; i < cards.size(); i++)
		{
			DrawTexturePro(cards[i], { 0,0,(float)cards[i].width,(float)cards[i].height }, { 1026 + (float)(i * x),718, 91, 127 }, { 0,0 }, 0, WHITE);
		}
	}
}

void InputMenu::load_combat()
{
	attack = LoadTexture("../Assets/attack.png");
	defense = LoadTexture("../Assets/defense.png");
}

void InputMenu::unload_combat()
{
	UnloadTexture(attack);
	UnloadTexture(defense);
}

void InputMenu::draw_combat(int damage, int a)
{
	if (a == 1)
	{
		DrawTexturePro(attack, { 0,0,(float)attack.width,(float)attack.height }, { 1021,630,516,252 }, { 0,0 }, 0, WHITE);
		DrawTextEx(font, to_string(damage).c_str(), { 1461,821 }, 30, 2, WHITE);
	}
	else
	{
		DrawTexturePro(defense, { 0,0,(float)defense.width,(float)defense.height }, { 1021,630,516,252 }, { 0,0 }, 0, WHITE);
	}
}

void InputMenu::load_YN()
{
	button = LoadTexture("../Assets/button_action.png");
}

void InputMenu::unload_YN()
{
	UnloadTexture(button);
}

void InputMenu::draw_YN(int a)
{
	if (a == 1)
	{
		DrawTextEx(font, "Do you want to use Dracula's ability?", { 908,684 }, 30, 2, WHITE);
		DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 949,749,225,66 }, { 0,0 }, 0, WHITE);
		Vector2 t1 = MeasureTextEx(font, "YES", 25, 2);
		DrawTextEx(font, "YES", { 942 + (225 - t1.x) / 2,749 + (66 - t1.y) / 2 }, 25, 2, WHITE);
		DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 1210,749,225,66 }, { 0,0 }, 0, WHITE);
		Vector2 t2 = MeasureTextEx(font, "NO", 25, 2);
		DrawTextEx(font, "NO", { 1210 + (225 - t2.x) / 2,749 + (66 - t2.y) / 2 }, 25, 2, WHITE);
	}
	else if (a == 2)
	{
		DrawTextEx(font, "Do you want to discard a card?", { 1060,697 }, 30, 2, WHITE);
		DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 949,749,225,66 }, { 0,0 }, 0, WHITE);
		Vector2 t1 = MeasureTextEx(font, "YES", 25, 2);
		DrawTextEx(font, "YES", { 942 + (225 - t1.x) / 2,749 + (66 - t1.y) / 2 }, 25, 2, WHITE);
		DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 1210,749,225,66 }, { 0,0 }, 0, WHITE);
		Vector2 t2 = MeasureTextEx(font, "NO", 25, 2);
		DrawTextEx(font, "NO", { 1210 + (225 - t2.x) / 2,749 + (66 - t2.y) / 2 }, 25, 2, WHITE);
	}
	else if (a == 3)
	{
		DrawTextEx(font, "Do you want to move Invisible_Man?", { 1060,697 }, 30, 2, WHITE);
		DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 949,749,225,66 }, { 0,0 }, 0, WHITE);
		Vector2 t1 = MeasureTextEx(font, "YES", 25, 2);
		DrawTextEx(font, "YES", { 942 + (225 - t1.x) / 2,749 + (66 - t1.y) / 2 }, 25, 2, WHITE);
		DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 1210,749,225,66 }, { 0,0 }, 0, WHITE);
		Vector2 t2 = MeasureTextEx(font, "NO", 25, 2);
		DrawTextEx(font, "NO", { 1210 + (225 - t2.x) / 2,749 + (66 - t2.y) / 2 }, 25, 2, WHITE);
	}
}

int InputMenu::check_YN(int a)
{
	if (a == 1)
	{
		Vector2 mouse = GetMousePosition();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (CheckCollisionPointRec(mouse, { 949,749,225,66 }))
			{
				return 1;
			}
			else if (CheckCollisionPointRec(mouse, { 1210,749,225,66 }))
			{
				return 0;
			}
		}
	}
	return -1;
}

void InputMenu::draw_text(std::string text)
{
	Vector2 t = MeasureTextEx(font, text.c_str(), 25, 2);
	DrawTextEx(font, text.c_str(), { 1015 + (507 - t.x) / 2,671 + (172 - t.y) / 2 }, 25, 2, WHITE);
}

void InputMenu::draw_none()
{
	Rectangle b;
	b = { 1109,777,165,48 };
	Vector2 t1 = MeasureTextEx(font, "NONE", 20, 2);
	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, b, { 0,0 }, 0, WHITE);
	DrawTextEx(font, "NONE", { b.x + (b.width - t1.x) / 2,b.y + (b.height - t1.y) / 2 }, 20, 2, WHITE);
}

std::vector<Texture2D> InputMenu::load_hand(const std::vector<std::string>& hand)
{
	std::vector<Texture2D> result;
	for (auto& x : hand)
	{
		result.emplace_back(LoadTexture(x.c_str()));
	}
	return result;
}

void InputMenu::unload_hand(std::vector<Texture2D>& hand)
{
	for (auto& x : hand)
	{
		UnloadTexture(x);
	}
}

void InputMenu::draw_fog(std::vector<int> cells)
{
	DrawTextEx(font, "Which fog do you want to move?", { 1060,697 }, 30, 2, WHITE);
	Vector2 t = MeasureTextEx(font, "00", 25, 2);
	DrawRectangle(1079, 752, 87, 66, WHITE);
	DrawTextEx(font, to_string(cells[0]).c_str(), { 1079 + (87 - t.x) / 2,752 + (66 - t.y) / 2 }, 25, 2, BLUE);
	DrawRectangle(1225, 752, 87, 66, WHITE);
	DrawTextEx(font, to_string(cells[1]).c_str(), { 1225 + (87 - t.x) / 2,752 + (66 - t.y) / 2 }, 25, 2, BLUE);
	DrawRectangle(1369, 752, 87, 66, WHITE);
	DrawTextEx(font, to_string(cells[2]).c_str(), { 1369 + (87 - t.x) / 2,752 + (66 - t.y) / 2 }, 25, 2, BLUE);
}

int InputMenu::check_fog()
{
	Vector2 mouse = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (CheckCollisionPointRec(mouse, { 1079, 752, 87, 66 }))
		{
			return 0;
		}
		if (CheckCollisionPointRec(mouse, { 1225, 752, 87, 66 }))
		{
			return 1;
		}
		if (CheckCollisionPointRec(mouse, { 1369, 752, 87, 66 }))
		{
			return 2;
		}
	}
	return -1;
}


