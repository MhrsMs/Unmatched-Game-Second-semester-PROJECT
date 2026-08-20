#include "FirstMenu.h"

int FirstMenu::run_first()
{
    load_first();
    int result;
    while (!WindowShouldClose())
    {
        update();
        result = checkButtons_first();
        if (result != -1)
        {
            break;
        }
        BeginDrawing();
        draw_first();
        EndDrawing();
    }
    unload_first();
    return result;
}

std::vector<int> FirstMenu::run_age()
{
    load_age();
    std::vector <int> result;
    num_age1.reset();
    num_age2.reset();
    activeInput = 0;
    while (!WindowShouldClose())
    {
        update();
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (num_age1.isMouseOver(age1rect))
            {
                activeInput = 1;
                num_age1.reset();
            }
            else if (num_age2.isMouseOver(age2rect))
            {
                activeInput = 2;
                num_age2.reset();
            }
            else if (!CheckCollisionPointRec(mouse, okrect))
            {
                activeInput = 0;
            }
            if (CheckCollisionPointRec(mouse, okrect))
            {
                if (!num_age1.isEmpty() && !num_age2.isEmpty())
                {
                    result.emplace_back(num_age1.getNumber());
                    result.emplace_back(num_age2.getNumber());
                    break;
                }
            }
        }
        if (activeInput == 1)
        {
            num_age1.update();

        }
        else if (activeInput == 2)
        {
            num_age2.update();
        }
        BeginDrawing();
        draw_age();
        EndDrawing();
    }
    unload_age();
    return result;
}

std::vector<int> FirstMenu::run_legend(int a)
{
    load_legend();
    std::vector <int> result;
    while (!WindowShouldClose())
    {
        update();
        int b1 = checkbuttons_legend();
        if (b1 != 0)
        {
            result.emplace_back(b1);
            break;
        }
        BeginDrawing();
        draw_legend(a, 0);
        EndDrawing();

    }

    while (!WindowShouldClose())
    {
        update();
        int b2 = checkbuttons_legend();
        if (b2 != 0 && b2 != result[0])
        {
            result.emplace_back(b2);
            break;
        }
        BeginDrawing();
        if (a == 1)
        {
            draw_legend(2, result[0]);
        }
        else
        {
            draw_legend(1, result[0]);
        }
        EndDrawing();
    }
    unload_legend();
    return result;
}

void FirstMenu::load_first()
{
    back = LoadTexture("../Assets/first_back.png");
    button = LoadTexture("../Assets/button_first.png");
    unmatched = LoadTexture("../Assets/unmatched.png");

    startrect = { 549,355,503,148 };
    loadrect = { 549,518,503,148 };
    exitrect = { 549,680,503,148 };


}

void FirstMenu::load_age()
{
    age = LoadTexture("../Assets/first_age.png");
    age1rect = { 781,329,615,86 };
    age2rect = { 781,525,615,86 };
    okrect = { 556,702,488,102 };
}

void FirstMenu::load_legend()
{
    legend = LoadTexture("../Assets/first_legend.png");
    dark = LoadTexture("../Assets/dark.png");
    legend1rect = { 110,285,393,392 };
    legend2rect = { 600,285,393,393 };
    legend3rect = { 1090,285,393,393 };
}

void FirstMenu::unload_first()
{
    UnloadTexture(unmatched);
    UnloadTexture(button);
    UnloadTexture(back);

}

void FirstMenu::unload_age()
{
    UnloadTexture(age);
}

void FirstMenu::unload_legend()
{
    UnloadTexture(dark);
    UnloadTexture(legend);
}

void FirstMenu::update()
{
}

void FirstMenu::draw_first()
{
    ClearBackground(BLACK);
    DrawTexturePro(back, { 0,0,(float)back.width,(float)back.height }, { 0,0,1600,900 }, { 0,0 }, 0, WHITE);
    DrawTexturePro(unmatched, { 0,0,(float)unmatched.width,(float)unmatched.height }, { 318,-86,964,542 }, { 0,0 }, 0, WHITE);

    DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, startrect, { 0,0 }, 0, WHITE);
    Vector2 t1 = MeasureTextEx(font, "START GAME", 49, 2);
    DrawTextEx(font, "START GAME", { startrect.x + (startrect.width - t1.x) / 2,startrect.y + (startrect.height - t1.y) / 2 }, 49, 2, BLACK);

    DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, loadrect, { 0,0 }, 0, WHITE);
    Vector2 t2 = MeasureTextEx(font, "LOAD GAME", 49, 2);
    DrawTextEx(font, "LOAD GAME", { loadrect.x + (loadrect.width - t2.x) / 2,loadrect.y + (loadrect.height - t2.y) / 2 }, 49, 2, BLACK);

    DrawTexturePro(button, { 0,0,(float)button.width,(float)button.height }, exitrect, { 0,0 }, 0, WHITE);
    Vector2 t4 = MeasureTextEx(font, "EXIT", 49, 2);
    DrawTextEx(font, "EXIT", { exitrect.x + (exitrect.width - t4.x) / 2,exitrect.y + (exitrect.height - t4.y) / 2 }, 49, 2, BLACK);


}

void FirstMenu::draw_age()
{
    ClearBackground(BLACK);
    DrawTexturePro(age, { 0,0,(float)age.width,(float)back.height }, { 0,0,1600,900 }, { 0,0 }, 0, WHITE);


    num_age1.draw(age1rect, activeInput == 1);
    num_age2.draw(age2rect, activeInput == 2);

}

void FirstMenu::draw_legend(int a, int b)
{
    ClearBackground(BLACK);
    DrawTexturePro(legend, { 0,0,(float)legend.width,(float)legend.height }, { 0,0,1600,900 }, { 0,0 }, 0, WHITE);
    if (a == 1)
    {
        DrawTextEx(font, "1", { 889 ,75 }, 77, 2, WHITE);
    }
    else
    {
        DrawTextEx(font, "2", { 889 ,75 }, 77, 2, WHITE);
    }
    if (b == 2)
    {
        DrawTexturePro(dark, { 0,0,(float)dark.width,(float)dark.height }, legend1rect, { 0,0 }, 0, WHITE);
    }
    else if (b == 3)
    {
        DrawTexturePro(dark, { 0,0,(float)dark.width,(float)dark.height }, legend2rect, { 0,0 }, 0, WHITE);
    }
    else if (b == 1)
    {
        DrawTexturePro(dark, { 0,0,(float)dark.width,(float)dark.height }, legend3rect, { 0,0 }, 0, WHITE);
    }
}

int FirstMenu::checkButtons_first()
{
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, startrect))
        {
            return 1;
        }
        if (CheckCollisionPointRec(mouse, loadrect))
        {
            return 2;

        }
        if (CheckCollisionPointRec(mouse, exitrect))
        {
            return 3;
        }
    }
    return -1;
}

int FirstMenu::checkbuttons_legend()
{
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mouse, legend1rect))
        {
            return 2;

        }
        else if (CheckCollisionPointRec(mouse, legend2rect))
        {
            return 3;

        }
        else if (CheckCollisionPointRec(mouse, legend3rect))
        {
            return 1;
        }

    }
    return 0;
}
