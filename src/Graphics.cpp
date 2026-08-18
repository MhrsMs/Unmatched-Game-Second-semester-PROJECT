#include "Graphics.h"
#include "InputNumber.h"
#include <iostream>
using namespace std;
Graphics::Graphics()
{
}
/*
action_menu.load_run();
action_menu.load_map(map);
action_menu.load_cards();
while (!WindowShouldClose())
{
    BeginDrawing();
    action_menu.draw_run(turn);
    action_menu.draw_map(map);
    action_menu.draw_cards();
    EndDrawing();
    WaitTime(3);
        break;
}
action_menu.unload_run();
action_menu.unload_map(map);
action_menu.unload_cards();
*/
/*
action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();

    int result = -1;
    while (!WindowShouldClose())
    {
        if(is_new_click())
        {
            result = ;
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();

        EndDrawing();
    }

    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    return result;
*/
int Graphics::get_card(int a, int cards)
{

    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    input.load_card();
    if (a == 3 || a == 5)
    {
        input.load_YN();
    }
    int result = -1;
    string text;
    switch (a)
    {
    case 1:
    {
        text = "Which card do you want to discard?";
        break;
    }
    case 2:
    {
        text = "which card do you want to play?";
        break;
    }
    case 3:
    {
        text = "Which card do you want to discard?";
        break;
    }
    case 4:
    {
        text = "Which card do you want to\n move to the top of your deck";
        break;
    }
    case 5:
    {
        text = "which card do you want to play?";
        break;
    }
    default:
    {
        text = " ";
        break;
    }
    }
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = input.check_cards(1, cards);
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        input.draw_text(text);
        if (a == 3 || a == 5)
        {
            input.draw_none();
        }
        if (result != -1)
        {
            break;
        }
        is_in_action();
        EndDrawing();
    }
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    input.unload_card();
    if (a == 3 || a == 5)
    {
        input.unload_YN();
    }
    return result;
}

void Graphics::end_game(int a)
{
    action_menu.load_run();
    action_menu.load_map(map);
    while (!WindowShouldClose())
    {

        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_winner(a);
        EndDrawing();
        WaitTime(5);
        break;

    }
    action_menu.unload_run();
    action_menu.unload_map(map);
}

int Graphics::movement1(int a, std::vector<ActionMenu::cell>& current_cell, std::string name, int move)
{
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    input.load_card();
    input.load_movement();
    int result = -1;
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = input.check_movement(current_cell);
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        input.draw_movement(a, current_cell, name, move);
        is_in_action();
        EndDrawing();
    }
    input.unload_movement();
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    input.unload_card();
    return result;
}

int Graphics::ability()
{
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    input.load_YN();
    int result = -1;
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = input.check_YN(1);
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        input.draw_YN(1);
        EndDrawing();
    }
    input.unload_YN();
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    return result;
}

void Graphics::text(int a, string t)
{
    string text;
    if (t == "")
    {
        switch (a)
        {
        case 1:
        {
            text = "There is no hero next to Dracula.\n He can't use his ability";
            break;
        }
        case 2:
        {
            text = "You must move the Hero 2 cells";
            break;
        }
        case 3:
        {
            text = "You must move the Hero 3 cells";
            break;
        }
        case 4:
        {
            text = "Your ally is in this cell.\nYou can't stay here.";
            break;
        }
        case 5:
        {
            text = "You must continue your move";
            break;
        }
        case 6:
        {
            text = "This space already contains fog.\n You can't place the fog here.";
            break;
        }
        case 7:
        {
            text = "This hero cannot access the other characters.\n Please select another hero";
            break;
        }
        case 8:
        {
            text = "This hero has no active card.\n Please select another hero";
            break;
        }
        default:
        {
            text = " "; break;
        }
        }
    }
    else
    {
        text = t;
    }

    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    input.load_card();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        input.draw_text(text);
        is_in_action();
        EndDrawing();
        WaitTime(3);
        break;
    }
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    input.unload_card();
}

int Graphics::get_number()
{
    InputNumber num;
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    input.load_card();
    num.reset();
    int result = -1;
    bool active = 0;
    Rectangle rect = { 1183,738,173,39 };
    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        if (is_new_click())
        {
            if (num.isMouseOver(rect))
            {
                active = 1;
                num.reset();
            }
            if (CheckCollisionPointRec(mouse, { 1210, 799, 120, 27 }))
            {
                if (!num.isEmpty())
                {
                    result = num.getNumber();
                    break;
                }
            }
        }
        num.update();
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        DrawTextEx(action_menu.font, "Enter Number :", { 1148,684 }, 25, 2, WHITE);
        DrawRectangle(1183, 738, 173, 39, WHITE);
        DrawRectangle(1210, 799, 120, 27, WHITE);
        DrawTextEx(action_menu.font, "OK", { 1251,799 }, 25, 2, BLACK);
        num.draw(rect, active);
        is_in_action();
        EndDrawing();
    }

    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    input.unload_card();
    return result;
}

int Graphics::get_hero(int a, const std::vector<std::string>& heros)
{
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    input.load_card();
    vector <Texture2D> t = input.load_hero(heros);
    int result = -1;
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = input.check_hero(heros.size());
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        input.draw_hero(a, t);
        is_in_action();
        EndDrawing();
    }
    input.unload_hero(t);
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    input.unload_card();
    return result;
}

void Graphics::combat(int a, int damage)
{
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    input.load_combat();
    input.load_card();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        input.draw_combat(damage, a);
        is_in_action();
        EndDrawing();
        WaitTime(5);
        break;
    }
    input.unload_combat();
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    input.unload_card();
}

int Graphics::run_first()
{
    int a = first.run_first();
    return a;
}

vector <int> Graphics::run_age()
{
    vector <int> a = first.run_age();
    return a;
}

vector <int> Graphics::run_legend(int a)
{
    vector <int> b = first.run_legend(a);
    return b;
}

int Graphics::maneuver()
{
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    input.load_maneuver();
    int result = -1;
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = input.check_maneuver();
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        input.draw_maneuver();
        EndDrawing();
    }
    input.unload_maneuver();
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    return result;

}

int Graphics::run_action()
{
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    action_menu.load_action();
    int result = -1;
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = action_menu.checkAction();
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        action_menu.draw_action();
        EndDrawing();
    }
    action_menu.unload_action();
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    return result;
}

int Graphics::help()
{
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    action_menu.load_help();
    int result = -1;
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = action_menu.check_help();
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        action_menu.draw_help();
        EndDrawing();
    }
    action_menu.unload_help();
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    return result;
}

int Graphics::get_card_target(const std::vector<string>& hand)
{
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    input.load_card();
    vector <Texture2D> t = input.load_hand(hand);
    int result = -1;
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = input.check_cards(2, hand.size());
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        input.draw_hand(t);
        is_in_action();
        EndDrawing();
    }
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    input.unload_hand(t);
    input.unload_card();
    return result;
}

int Graphics::get_card_action(const std::vector<string>& cards)
{
    action_menu.load_run();
    action_menu.load_map(map);
    vector <Texture2D> t = action_menu.load_cards_action(cards);
    int result = -1;
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = input.check_cards(1, cards.size());
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards_action(t);
        input.draw_text("which card do you want to play?");
        EndDrawing();
    }

    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards_action(t);
    return result;
}

void Graphics::show_hand(const std::vector<string>& hand)
{
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    input.load_card();
    vector <Texture2D> t = input.load_hand(hand);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        input.draw_hand(t);
        is_in_action();
        EndDrawing();
        WaitTime(3);
        break;
    }
    input.unload_hand(t);
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    input.unload_card();

}

bool Graphics::is_new_click()
{
    if (click)
    {
        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            click = 0;
        }
        return 0;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        click = 1;
        return 1;
    }
    return 0;
}

int Graphics::yes_or_no(int a)
{
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    input.load_YN();
    input.load_card();
    int result = -1;
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = input.check_YN(1);
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        input.draw_YN(a);
        is_in_action();
        EndDrawing();
    }
    input.unload_YN();
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    return result;
}

int Graphics::get_foggy_cell(std::vector<int> cells)
{
    action_menu.load_run();
    action_menu.load_map(map);
    action_menu.load_cards();
    int result = -1;
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = input.check_fog();
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        action_menu.draw_run(turn);
        action_menu.draw_map(map);
        action_menu.draw_cards();
        input.draw_fog(cells);
        is_in_action();
        EndDrawing();
    }
    input.unload_card();
    action_menu.unload_run();
    action_menu.unload_map(map);
    action_menu.unload_cards();
    return result;

}

int Graphics::get_save(int a, std::vector<std::string> time)
{

    input.load_save();
    int result = -1;
    while (!WindowShouldClose())
    {
        if (is_new_click())
        {
            result = input.check_save(1);
        }
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        input.draw_save(a, time);
        EndDrawing();
    }
    input.unload_save();
    return result;
}


void Graphics::is_in_action()
{
    if (action_menu.action.is_thiscard)
    {
        input.draw_card(action_menu.action.thiscard);
    }
}

