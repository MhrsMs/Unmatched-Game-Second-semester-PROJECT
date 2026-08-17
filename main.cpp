#include "FirstMenu.h"
#include "GameManager.h"
#include <iostream>
using namespace std;
int main() {
    
    InitWindow(1600, 900, "UNMATCHED");
    SetTargetFPS(60);
    try 
    {
        
        GameManager gm;
        gm.run();
        
    }
    catch(const exception& e)
    {
        DrawText(e.what(), 800, 400, 25, WHITE);
    }
    catch (...)
    {
        DrawText("Unknown error occurred!", 800, 400, 25, WHITE);
    }
    CloseWindow();
    return 0;
}