#include "ActionMenu.h"
using namespace std;
ActionMenu::ActionMenu()
{
}

ActionMenu::~ActionMenu()
{
	unload_run();
	unload_action();
	UnloadTexture(action.thiscard);
}

void ActionMenu::load_run()
{
	back = LoadTexture("../Assets/action_back.png");
	for (int i = 0; i < player1.size(); i++)
	{
		player1photo.emplace_back(LoadTexture(player1[i].c_str()));
		if (player1[i] == "../Assets/invisible_man_cell.png")
		{
			for (int i = 0; i < 3; i++)
			{
				player1photo.emplace_back(LoadTexture("../Assets/fog_cell.png"));
			}
		}
	}
	for (int i = 0; i < player2.size(); i++)
	{
		player2photo.emplace_back(LoadTexture(player2[i].c_str()));
		if (player2[i] == "../Assets/invisible_man_cell.png")
		{
			for (int i = 0; i < 3; i++)
			{
				player2photo.emplace_back(LoadTexture("../Assets/fog_cell.png"));
			}
		}
	}
	if (player1[0] == "../Assets/invisible_man_cell.png" || player2[0] == "../Assets/invisible_man_cell.png")
	{
		fog = LoadTexture("../Assets/fog.png");
	}
	backdra = LoadTexture("../Assets/dracula/backDra.png");
	backsher = LoadTexture("../Assets/holms/backSher.png");
	backman = LoadTexture("../Assets/InvisibleMan/backMan.png");
}


void ActionMenu::load_action()
{
	button = LoadTexture("../Assets/button_action.png");
	help = LoadTexture("../Assets/help.png");

}

void ActionMenu::load_cards()
{

	for (auto& x : action.cards)
	{
		action.cardsPhoto.emplace_back(LoadTexture(x.c_str()));
	}
}

void ActionMenu::unload_run()
{
	UnloadTexture(back);
	for (auto& x : player1photo)
	{
		UnloadTexture(x);
	}
	for (auto& x : player2photo)
	{
		UnloadTexture(x);
	}
	player1photo.clear();
	player2photo.clear();
}

void ActionMenu::unload_action()
{
	UnloadTexture(button);
	UnloadTexture(help);

}

void ActionMenu::unload_cards()
{
	for (auto& x : action.cardsPhoto)
	{
		UnloadTexture(x);
	}
	action.cardsPhoto.clear();
}

void ActionMenu::draw_run(int a)
{
	ClearBackground(BLACK);
	DrawTexture(back, 0, 0, WHITE);
	if (player1[0] == "../Assets/dracula_cell.png")
	{
		DrawTexturePro(player1photo[0], { 0,0,(float)player1photo[0].width,(float)player1photo[0].height }, { 70,92 ,213,213 }, { 0,0 }, 0, WHITE);
		Vector2 t = MeasureTextEx(font, "DRACULA", 25, 2);
		DrawTextEx(font, "DRACULA", { 176 - (t.x) / 2,285 }, 25, 2, RED);
		string h0 = to_string(action.healthPlayer1[0]) + "/13";
		string h1 = to_string(action.healthPlayer1[1]) + "/1";
		string h2 = to_string(action.healthPlayer1[2]) + "/1";
		string h3 = to_string(action.healthPlayer1[3]) + "/1";
		DrawTextEx(font, h0.c_str(), { 153,311 }, 25, 2, RED);
		DrawTexturePro(player1photo[1], { 0,0,(float)player1photo[1].width,(float)player1photo[1].height }, { 52,459 ,75,75 }, { 0,0 }, 0, WHITE);
		DrawTextEx(font, h1.c_str(), { 72,551 }, 25, 2, RED);
		DrawTexturePro(player1photo[2], { 0,0,(float)player1photo[2].width,(float)player1photo[2].height }, { 142,459 ,75,75 }, { 0,0 }, 0, WHITE);
		DrawTextEx(font, h2.c_str(), { 160,551 }, 25, 2, RED);
		DrawTexturePro(player1photo[3], { 0,0,(float)player1photo[3].width,(float)player1photo[3].height }, { 233,459 ,75,75 }, { 0,0 }, 0, WHITE);
		DrawTextEx(font, h3.c_str(), { 249,551 }, 25, 2, RED);
	}
	else if (player1[0] == "../Assets/invisible_man_cell.png")
	{
		DrawTexturePro(player1photo[0], { 0,0,(float)player1photo[0].width,(float)player1photo[0].height }, { 70,92 ,213,213 }, { 0,0 }, 0, WHITE);
		string h0 = to_string(action.healthPlayer1[0]) + "/15";
		Vector2 t = MeasureTextEx(font, "INVISIBLE_MAN", 25, 2);
		DrawTextEx(font, "INVISIBLE_MAN", { 176 - (t.x) / 2,285 }, 25, 2, BLUE);
		DrawTextEx(font, h0.c_str(), { 153,311 }, 25, 2, BLUE);
		DrawTexturePro(fog, { 0,0,(float)fog.width,(float)fog.height }, { 38,460 ,280,176 }, { 0,0 }, 0, WHITE);
	}
	else if (player1[0] == "../Assets/sherlock_cell.png")
	{
		DrawTexturePro(player1photo[0], { 0,0,(float)player1photo[0].width,(float)player1photo[0].height }, { 70,92 ,213,213 }, { 0,0 }, 0, WHITE);
		string h0 = to_string(action.healthPlayer1[0]) + "/16";
		string h1 = to_string(action.healthPlayer1[1]) + "/8";
		Vector2 t = MeasureTextEx(font, "SHERLOCK", 25, 2);
		DrawTextEx(font, "SHERLOCK", { 176 - (t.x) / 2,285 }, 25, 2, YELLOW);
		DrawTextEx(font, h0.c_str(), { 153,311 }, 25, 2, YELLOW);
		DrawTexturePro(player1photo[1], { 0,0,(float)player1photo[1].width,(float)player1photo[1].height }, { 142,459 ,75,75 }, { 0,0 }, 0, WHITE);
		DrawTextEx(font, h1.c_str(), { 160,551 }, 25, 2, YELLOW);
	}
	if (player2[0] == "../Assets/dracula_cell.png")
	{
		DrawTexturePro(player2photo[0], { 0,0,(float)player2photo[0].width,(float)player2photo[0].height }, { 1319,92 ,213,213 }, { 0,0 }, 0, WHITE);
		string h0 = to_string(action.healthPlayer2[0]) + "/13";
		string h1 = to_string(action.healthPlayer2[1]) + "/1";
		string h2 = to_string(action.healthPlayer2[2]) + "/1";
		string h3 = to_string(action.healthPlayer2[3]) + "/1";
		Vector2 t = MeasureTextEx(font, "DRACULA", 25, 2);
		DrawTextEx(font, "DRACULA", { 1424 - (t.x / 2),285 }, 25, 2, RED);
		DrawTextEx(font, h0.c_str(), { 1399,311 }, 25, 2, RED);
		DrawTexturePro(player2photo[1], { 0,0,(float)player2photo[1].width,(float)player2photo[1].height }, { 1299,459 ,75,75 }, { 0,0 }, 0, WHITE);
		DrawTextEx(font, h1.c_str(), { 1317,551 }, 25, 2, RED);
		DrawTexturePro(player2photo[2], { 0,0,(float)player2photo[2].width,(float)player2photo[2].height }, { 1389,459 ,75,75 }, { 0,0 }, 0, WHITE);
		DrawTextEx(font, h2.c_str(), { 1408,551 }, 25, 2, RED);
		DrawTexturePro(player2photo[3], { 0,0,(float)player2photo[3].width,(float)player2photo[3].height }, { 1480,459 ,75,75 }, { 0,0 }, 0, WHITE);
		DrawTextEx(font, h3.c_str(), { 1501,551 }, 25, 2, RED);
	}
	else if (player2[0] == "../Assets/invisible_man_cell.png")
	{
		DrawTexturePro(player2photo[0], { 0,0,(float)player2photo[0].width,(float)player2photo[0].height }, { 1319,92 ,213,213 }, { 0,0 }, 0, WHITE);
		string h0 = to_string(action.healthPlayer2[0]) + "/15";
		Vector2 t = MeasureTextEx(font, "INVISIBLE_MAN", 25, 2);
		DrawTextEx(font, "INVISIBLE_MAN", { 1424 - (t.x / 2),285 }, 25, 2, BLUE);

		DrawTextEx(font, h0.c_str(), { 1399,311 }, 25, 2, BLUE);
		DrawTexturePro(fog, { 0,0,(float)fog.width,(float)fog.height }, { 1285,460 ,280,176 }, { 0,0 }, 0, WHITE);
	}
	else if (player2[0] == "../Assets/sherlock_cell.png")
	{
		DrawTexturePro(player2photo[0], { 0,0,(float)player2photo[0].width,(float)player2photo[0].height }, { 1319,92 ,213,213 }, { 0,0 }, 0, WHITE);
		string h0 = to_string(action.healthPlayer2[0]) + "/16";
		string h1 = to_string(action.healthPlayer2[1]) + "/8";
		Vector2 t = MeasureTextEx(font, "SHERLOCK", 25, 2);
		DrawTextEx(font, "SHERLOCK", { 1424 - (t.x / 2),285 }, 25, 2, YELLOW);
		DrawTextEx(font, h0.c_str(), { 1399,311 }, 25, 2, YELLOW);
		DrawTexturePro(player2photo[1], { 0,0,(float)player2photo[1].width,(float)player2photo[1].height }, { 1389,459 ,75,75 }, { 0,0 }, 0, WHITE);
		DrawTextEx(font, h1.c_str(), { 1408,551 }, 25, 2, YELLOW);
	}
	draw_change_turn(a);
}

void ActionMenu::load_map(std::vector <cell>& map)
{
	for (auto& x : map)
	{
		x.photo = LoadTexture(x.heroPhoto.c_str());
	}
}

void ActionMenu::unload_map(std::vector<cell>& map)
{
	for (auto& x : map)
	{
		UnloadTexture(x.photo);
	}
}

void ActionMenu::draw_map(std::vector <cell>& map)
{
	for (size_t i = 0; i < map.size(); i++)
	{
		DrawTexturePro(map[i].photo, { 0,0,(float)map[i].photo.width,(float)map[i].photo.height }, { map[i].x,map[i].y,67,67 }, { 0,0 }, 0, WHITE);
	}
}

void ActionMenu::draw_action()
{
	DrawTexturePro(help, { 0,0,(float)help.width,(float)help.height }, { 769,5,63,45 }, { 0,0 }, 0, WHITE);
	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 859,677,225,67 }, { 0,0 }, 0, WHITE);
	Vector2 t1 = MeasureTextEx(font, "MANEUVER", 25, 2);
	DrawTextEx(font, "MANEUVER", { 859 + (225 - t1.x) / 2,677 + (67 - t1.y) / 2 }, 25, 2, WHITE);

	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 1084,677,225,67 }, { 0,0 }, 0, WHITE);
	Vector2 t2 = MeasureTextEx(font, "SCHEME", 25, 2);
	if (action.canScheme)
	{
		DrawTextEx(font, "SCHEME", { 1084 + (225 - t2.x) / 2,677 + (67 - t2.y) / 2 }, 25, 2, WHITE);
	}
	else
	{
		DrawTextEx(font, "SCHEME", { 1084 + (225 - t2.x) / 2,677 + (67 - t2.y) / 2 }, 25, 2, RED);
		Vector2 a = MeasureTextEx(font, action.SchemeReason.c_str(), 15, 2);
		DrawTextEx(font, action.SchemeReason.c_str(), { 955 + (483 - a.x) / 2,841 + (22 - a.y) / 2 }, 15, 2, RED);
	}
	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 1309,677,225,67 }, { 0,0 }, 0, WHITE);
	Vector2 t3 = MeasureTextEx(font, "ATTACK", 25, 2);
	if (action.canAttack)
	{
		DrawTextEx(font, "ATTACK", { 1309 + (225 - t3.x) / 2,677 + (67 - t3.y) / 2 }, 25, 2, WHITE);
	}
	else
	{
		DrawTextEx(font, "ATTACK", { 1309 + (225 - t3.x) / 2,677 + (67 - t3.y) / 2 }, 25, 2, RED);
		Vector2 a = MeasureTextEx(font, action.AttackReason.c_str(), 15, 2);
		DrawTextEx(font, action.AttackReason.c_str(), { 955 + (483 - a.x) / 2,820 + (22 - a.y) / 2 }, 15, 2, RED);
	}

	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 859,753,225,67 }, { 0,0 }, 0, WHITE);
	Vector2 t4 = MeasureTextEx(font, "UNDO", 25, 2);
	DrawTextEx(font, "UNDO", { 859 + (225 - t4.x) / 2,753 + (67 - t4.y) / 2 }, 25, 2, WHITE);

	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 1084,753,225,67 }, { 0,0 }, 0, WHITE);
	Vector2 t5 = MeasureTextEx(font, "SAVE GAME", 25, 2);
	DrawTextEx(font, "SAVE GAME", { 1084 + (225 - t5.x) / 2,753 + (67 - t5.y) / 2 }, 25, 2, WHITE);

	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 1309,753,225,67 }, { 0,0 }, 0, WHITE);
	Vector2 t6 = MeasureTextEx(font, "EXIT", 25, 2);
	DrawTextEx(font, "EXIT", { 1309 + (225 - t6.x) / 2,753 + (67 - t6.y) / 2 }, 25, 2, WHITE);
}

void ActionMenu::draw_change_turn(int a)
{
	if (a == 1)
	{
		DrawTextEx(font, "1", { 805,615 }, 36, 2, WHITE);
	}
	else if (a == 2)
	{
		DrawTextEx(font, "2", { 805,615 }, 36, 2, WHITE);
	}
}

void ActionMenu::draw_cards()
{
	if (!action.cards.empty())
	{
		int x = 570 / action.cards.size();
		for (int i = 0; i < action.cards.size(); i++)
		{
			DrawTexturePro(action.cardsPhoto[i], { 0,0,(float)action.cardsPhoto[i].width,(float)action.cardsPhoto[i].height }, { (float)70 + (i * x),677,115,160 }, { 0,0 }, 0, WHITE);
		}
	}

}

void ActionMenu::draw_winner(int a)
{
	if (a == 1)
	{

		DrawTextEx(font, "PLAYER1 WIN", { 954,731 }, 60, 2, WHITE);
	}
	else
	{

		DrawTextEx(font, "PLAYER2 WIN", { 954,731 }, 60, 2, WHITE);
	}
}

void ActionMenu::load_help()
{
	help_text = LoadTexture("../Assets/help_text.png");
}

void ActionMenu::unload_help()
{
	UnloadTexture(help_text);
}

void ActionMenu::draw_help()
{
	ClearBackground(BLACK);
	DrawTexture(help_text, 0, 0, WHITE);
}

int ActionMenu::check_help()
{
	Vector2 mouse = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (CheckCollisionPointRec(mouse, { 0,0,1600,900 }))
		{
			return 1;
		}
	}
	return -1;
}

std::vector<Texture2D> ActionMenu::load_cards_action(std::vector<std::string> cards)
{
	std::vector<Texture2D> result;
	for (auto& x : cards)
	{
		result.emplace_back(LoadTexture(x.c_str()));
	}
	return result;
}

void ActionMenu::unload_cards_action(std::vector<Texture2D> cards)
{
	for (auto& x : cards)
	{
		UnloadTexture(x);
	}
}

void ActionMenu::draw_cards_action(std::vector<Texture2D> cards)
{
	if (!cards.empty())
	{
		int x = 570 / cards.size();
		for (int i = 0; i < cards.size(); i++)
		{
			DrawTexturePro(cards[i], { 0,0,(float)cards[i].width,(float)cards[i].height }, { (float)70 + (i * x),677,115,160 }, { 0,0 }, 0, WHITE);
		}
	}
}

int ActionMenu::checkAction()
{
	Vector2 mouse = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (CheckCollisionPointRec(mouse, { 859,677,225,67 }))
		{
			return 3;

		}
		else if (CheckCollisionPointRec(mouse, { 1084,677,225,67 }))
		{
			if (!action.canScheme)
			{
				return -1;
			}
			else
			{
				return 4;
			}
		}
		else if (CheckCollisionPointRec(mouse, { 1309,677,225,67 }))
		{
			if (!action.canAttack)
			{
				return -1;
			}
			else
			{
				return 5;
			}
		}
		else if (CheckCollisionPointRec(mouse, { 859,753,225,67 }))
		{
			return 2; //back
		}
		else if (CheckCollisionPointRec(mouse, { 1084,753,225,67 }))
		{
			return 6; //save
		}
		else if (CheckCollisionPointRec(mouse, { 1309,753,225,67 }))
		{
			return 1;
		}
		else if (CheckCollisionPointRec(mouse, { 769,5,63,45 }))
		{
			return 7; //help
		}
	}
	return -1;
}

void ActionMenu::draw_end_turn()
{
	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 942,723,237,69 }, { 0,0 }, 0, WHITE);
	Vector2 t1 = MeasureTextEx(font, "END TURN", 25, 2);
	DrawTextEx(font, "END TURN", { 943 + (237 - t1.x) / 2,723 + (69 - t1.y) / 2 }, 25, 2, WHITE);
	DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, { 1221,723,237,69 }, { 0,0 }, 0, WHITE);
	Vector2 t2 = MeasureTextEx(font, "UNDO", 25, 2);
	DrawTextEx(font, "UNDO", { 1221 + (237 - t2.x) / 2,723 + (69 - t2.y) / 2 }, 25, 2, WHITE);
}

int ActionMenu::check_end_turn()
{
	Vector2 mouse = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (CheckCollisionPointRec(mouse, { 942,723,237,69 }))
		{
			return 0;
		}
		else if (CheckCollisionPointRec(mouse, { 1221,723,237,69 }))
		{
			return 1;
		}
	}
	return -1;
}
