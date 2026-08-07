#include "FirstMenu.h"
#include <iostream>
using namespace std;
int main() {

    InitWindow(1600, 900, "UNMATCHED");
    SetTargetFPS(60);
    FirstMenu fm;
    vector <int> s;
    vector <int> d;
    int a = fm.run_first();
    if (a == 1)
    {
        s = fm.run_age();
        cout << s[0] << "    " << s[1] << endl;
        if (s[0] < s[1])
        {
            d = fm.run_legend(1);

        }
        else
        {
            d = fm.run_legend(2);

        }



        cout << d[0] << "    " << d[1] << endl;

    }

    CloseWindow();
    return 0;
}