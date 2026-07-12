#include "ConsoleView.h"
#include <iostream>
#include <iomanip>
void ConsoleView::print_error(string what)
{
    cout << what << endl;
}

void ConsoleView::print_map(vector<string> text)
{
    cout << "+=================================================" << "================================================+\n";
    cout << "|      [MAP]       *DR : Dracula *SH : Sherlock Holmes *DW : DR.Watson *S1,S2,S3 : Sisters        |\n";
    cout << "+=================================================" << "================================================+\n";
    cout << "\033[38;2;173;216;230m(" << text[1] << ")\033[0m-\033[38;2;173;216;230m(" << text[2] << ")\033[0m      \033[38;2;139;69;19m(" << text[3] << ")\033[0m------\033[38;2;139;69;19m(" << text[4] << ")\033[0m      \033[38;2;255;220;170m(" << text[5] << ")\033[0m------\033[38;2;255;220;170m(" << text[6] << ")\033[0m" << endl;
    cout << "  |      \\    /    \\    /    \\    /    \\" << endl;
    cout << "\033[38;2;173;216;230m(" << text[7] << ")\033[0m-\033[38;2;173;216;230m(" << text[8] << ")\033[0m-\033[38;2;139;69;19m(\033[0m\033[38;2;173;216;230m" << text[9] << "\033[0m\033[38;2;139;69;19m)\033[0m      \033[38;2;139;69;19m(" << text[10] << ")\033[0m------\033[38;2;139;69;19m(\033[0m\033[38;2;255;220;170m" << text[11] << "\033[0m\033[32m)\033[0m------\033[38;2;255;220;170m(" << text[12] << ")\033[0m" << endl;
    cout << "  |      \\  |                   |" << endl;
    cout << "\033[34m(" << text[13] << ")\033[0m-\033[34m(" << text[14] << ")\033[0m-\033[34m(\033[0m\033[38;2;173;216;230m" << text[15] << "\033[0m\033[34m)\033[0m           \033[32m(" << text[16] << ")\033[0m   |  \033[38;2;128;0;255m(" << text[17] << ")\033[0m" << endl;
    cout << "  |                     /    \\  | /    \\" << endl;
    cout << "\033[34m(\033[0m\033[38;2;221;160;221m" << 18 << "\033[0m\033[34m)\033[0m------\033[34m(\033[0m\033[32m" << text[19] << "\033[0m\033[34m)\033[0m------\033[32m(" << text[20] << ")\033[0m      \033[32m(\033[0m\033[38;2;128;0;255m" << text[21] << "\033[0m\033[32m)\033[0m-\033[38;2;128;0;255m(" << text[22] << ")\033[0m-\033[38;2;128;0;255m(" << text[23] << ")\033[0m" << endl;
    cout << "  |                /         /    \\         \\" << endl;
    cout << "  |            \033[32m(\033[0m\033[38;2;221;160;221m" << text[24] << "\033[0m\033[32m)\033[0m------\033[38;2;221;160;221m(" << text[25] << ")\033[0m------\033[38;2;221;160;221m(" << text[26] << ")\033[0m------\033[38;2;128;0;255m(\033[0m\033[38;2;221;160;221m" << text[27] << "\033[0m\033[38;2;128;0;255m)\033[0m" << endl;
    cout << "  |           /    \\    /              \\    /" << endl;
    cout << "\033[38;2;221;160;221m(" << text[28] << ")\033[0m-\033[38;2;221;160;221m(" << text[29] << ")\033[0m-\033[38;2;221;160;221m(" << text[30] << ")\033[0m------\033[38;2;221;160;221m(" << text[31] << ")\033[0m                \033[38;2;221;160;221m(" << text[32] << ")\033[0m" << endl << endl;
    cout << "cells 1, 6, 16, and 28 are secret passages\n";
}
void ConsoleView::print_Help()
{
    cout << "=========================================================================\n";
    cout << "                      UNMATCHED - DIGITAL MANUAL                         \n";
    cout << "=========================================================================\n\n";

    // --- GAME OVERVIEW ---
    cout << "-------------------------------------------------------------------------\n";
    cout << " [1] GAME OVERVIEW\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << " * Unmatched is a tactical combat game between two legendary heroes.\n";
    cout << " * Each hero has unique sidekicks and a custom 30-card deck.\n";
    cout << " * Objective: Reduce the enemy Hero's health to 0 to win the game.\n";
    cout << " * Hand Limit: Maximum of 7 cards at the end of your turn.\n\n";

    // --- MAP & MOVEMENT ---
    std::cout << "-------------------------------------------------------------------------\n";
    cout << " [2] MAP & MOVEMENT RULES\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << " * Grid: The map consists of 32 nodes divided into colored Zones.\n";
    cout << " * Adjacency: Nodes connected by lines are adjacent.\n";
    cout << " * Multi-zone: Nodes with two colors belong to both color zones.\n";
    cout << " * Occupancy: Only 1 fighter can occupy a single node at a time.\n";
    cout << " * Movement: You can pass through allies, but NOT through enemies.\n";
    cout << " * Secret Passages (Teleport): 4 nodes marked with arrows.\n";
    cout << "   -> Moving between secret passages costs exactly 1 Move Point.\n";
    cout << "   -> Passages cannot be used for melee adjacency attacks.\n\n";

    // --- TURN ACTIONS ---
    cout << "-------------------------------------------------------------------------\n";
    cout << " [3] TURN ACTIONS (You MUST perform exactly 2 actions per turn)\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << " A) MANEUVER:\n";
    cout << "    1. Draw 1 card from your deck (Mandatory).\n";
    cout << "       Note: If deck is empty, exhaustion deals 2 damage to your fighters!\n";
    cout << "    2. Move fighters up to their speed limit (Optional).\n";
    cout << "    3. Boost: Discard a card to add its BOOST value to your movement.\n\n";

    cout << " B) SCHEME (Event):\n";
    cout << "    - Play a yellow lightning card. Its effect resolves immediately.\n";
    cout << "    - The card's character must be alive to use it.\n\n";

    cout << " C) ATTACK:\n";
    cout << "    - Declare an active fighter and a valid target.\n";
    cout << "    - Melee Fighters: Can only attack adjacent targets.\n";
    cout << "    - Ranged Fighters: Can attack adjacent targets OR targets in the same Zone.\n";
    cout << "    - Combat Resolution:\n";
    cout << "      -> Attacker plays an Attack card (Red/Purple) face-down.\n";
    cout << "      -> Defender may play a Defense card (Blue/Purple) face-down.\n";
    cout << "      -> Effects resolve in order: Immediately -> During Combat -> After Combat.\n";
    cout << "      -> If timing ties occur, Defender's effect triggers first.\n\n";

    // --- HEROES STATS ---
    cout << "-------------------------------------------------------------------------\n";
    cout << " [4] HEROES & SIDEKICKS STATS\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << " +-------------------+----+------------+-------------+-----------------+\n";
    cout << " | Character         | HP | Move Speed | Combat Type | Sidekicks       |\n";
    cout << " +-------------------+----+------------+-------------+-----------------+\n";
    cout << " | DRACULA           | 13 |     2      |    Melee    | 3 Sisters (1HP) |\n";
    cout << " | SHERLOCK HOLMES   | 16 |     2      |    Melee    | Dr. Watson (8HP)|\n";
    cout << " +-------------------+----+------------+-------------+-----------------+\n";
    cout << " * Dr. Watson Combat Type: Ranged.\n";
    cout << " * Dracula's Ability: Start of turn, may deal 1 damage to an adjacent\n";
    cout << "   fighter (including Sisters) to draw 1 card.\n";
    cout << " * Sherlock's Ability: Character-specific cards (non-ANY) cannot be\n";
    cout << "   canceled or ignored by enemy card effects (e.g., Feint).\n\n";

    // --- MAIN MENU ---
    cout << "-------------------------------------------------------------------------\n";
    cout << " [5] MAIN MENU\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << " > Play      > Help          > Exit \n\n";

    // --- ACTION MENU ---
    cout << "-------------------------------------------------------------------------\n";
    cout << " [6] AVAILABLE IN-GAME COMMANDS\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << " > Maneuver      > Attack          > Scheme \n";
    cout << " > Help      > Back to main menu\n";
    cout << "=========================================================================\n";
}

int ConsoleView::print_main_menu()
{
    int a;
    while (1)
    {
        cout << "1 = PLAY GAME 2 = HELP 3 = EXIT" << endl;
        cin >> a;
        if (a > 0 && a < 4)
        {
            break;
        }
    }
    return a;
}

bool ConsoleView::print_ability()
{
    while (1)
    {
        int a;
        cout << "Do you want to use Dracula's ability? 1 = yes 0 = no" << endl;
        cin >> a;
        if (a == 0)
        {
            return 0;
        }
        if (a == 1)
        {
            return 1;
        }

    }

}

int ConsoleView::print_complet_needs(int c, vector<int> a, vector<string> b)
{
    switch (c)
    {
    case 1:
    {
        int s;
        while (1)
        {

            cout << "Enter the number of the cell where you want sister to return :" << endl;
            for (int i = 0; i < a.size(); i++)
            {
                cout << i << " = " << a[i] << " ";
            }
            cout << endl;
            cin >> s;
            if (s >= 0 && s < a.size())
            {
                break;
            }
        }
        return a[s];
    }
    case 2:
    {
        int s;
        while (1)
        {

            cout << "Enter the number of the cell where you want Dracula to be placed:" << endl;
            cin >> s;
            if (s >= 0 && s < 33)
            {
                break;
            }
        }
        return s;
    }
    case 3:
    {
        cout << "You must move the Hero 2 cells" << endl;
        return 0;
    }
    case 4:
    {
        int s;
        while (1)
        {

            cout << "Enter the number of the cell where you want Dracula to be placed:" << endl;
            for (int i = 0; i < a.size(); i++)
            {
                cout << i << " = " << a[i] << " ";
            }
            cout << endl;
            cin >> s;
            if (s >= 0 && s < a.size())
            {
                break;
            }
        }
        return s;
    }
    case 5:
    {
        cout << "You must move the Hero 3 cells" << endl;
        return 0;
    }
    case 6:
    {
        cout << "Which card do you want to discard? 0 = none " << endl;
        int s;
        while (1)
        {
            for (int i = 0; i < b.size(); i++)
            {
                cout << i + 1 << " = " << b[i] << " ";

            }
            cout << endl;
            cin >> s;
            if (s >= 1 && s <= b.size() + 1)
            {
                break;
            }
        }
        return s;
    }
    case 7:
    {
        int s;
        cout << "Enter number : " << endl;
        cin >> s;
        return s;
    }
    case 8:
    {
        int s;
        while (1)
        {
            cout << "Choose a hero :" << endl;
            for (int i = 0; i < b.size(); i++)
            {
                cout << i << " = " << b[i] << " ";

            }
            cout << endl;
            cin >> s;
            if (s >= 0 && s < b.size() + 1)
            {
                break;
            }

        }
        return s;
    }
    }
}

vector<string> ConsoleView::get_name()
{
    vector <string> name;
    string n1, n2;
    int a;
    cout << "Please enter the name of the younger player" << endl;
    cin >> n1;
    name.emplace_back(n1);
    cout << "Please enter the name of the older player" << endl;
    cin >> n2;
    name.emplace_back(n2);
    while (1)
    {
        cout << n1 << " Which one do you choose? 1 = DRACULA 2 = HOLMES" << endl;
        cin >> a;
        if (a > 0 && a < 3)
        {
            break;
        }
    }
    name.emplace_back(to_string(a));
    return name;
}

void ConsoleView::print_name(string name)
{
    cout << name << endl;
}

int ConsoleView::print_intitial_position(string name)
{
    int a;
    while (1)
    {
        cout << "Enter the initial position of " << name << endl;
        cin >> a;
        if (a > 0 && a < 33)
        {
            break;
        }
    }
    return a;
}

int ConsoleView::print_action_menu(ShowActionMenu s)
{
    if (s.card.size() < 5)
    {
        for (int i = s.card.size() - 1; i < 5; i++)
        {
            s.card.emplace_back(" ");
            s.kind.emplace_back(" ");
        }
    }
    int r;
    cout << "+=================================================" << "================================================+\n";
    cout << "|" << left << setw(48) << "PLAYER:" << "|" << left << setw(48) << s.name << "|" << endl;
    cout << "+=================================================" << "================================================+\n";
    for (int i = 0; i < s.nameOfHero.size(); i++)
    {
        cout << "|" << left << setw(9) << s.nameOfHero[i] << " *Health:" << s.health[i] << " *Move:" << s.move[i] << " *CellNumber:" << left << setw(57) << s.cell[i] << "|" << endl;
    }
    cout << "+=================================================" << "================================================+\n";
    cout << "|      [MAP]       *DR : Dracula *SH : Sherlock Holmes *DW : DR.Watson *S1,S2,S3 : Sisters        |\n";
    cout << "+=================================================" << "================================================+\n";
    print_map(s.text);
    cout << "+================================================+" << "================================================+\n";
    cout << "|                       HAND                     |" << "                     ACTION                     |\n";
    cout << "+================================================+" << "================================================+\n";
    cout << "|" << left << setw(24) << s.card[0] << left << setw(23) << s.kind[0] << "|" << left << setw(48) << "1 = Maneuver" << "|" << endl;
    cout << "|" << left << setw(24) << s.card[1] << left << setw(23) << s.kind[1] << "|" << left << setw(48) << "2 = Attack" << "|" << endl;
    cout << "|" << left << setw(24) << s.card[2] << left << setw(23) << s.kind[2] << "|" << left << setw(48) << "3 = Scheme" << "|" << endl;
    cout << "|" << left << setw(24) << s.card[3] << left << setw(23) << s.kind[3] << "|" << left << setw(48) << "4 = Exit" << "|" << endl;
    if (s.card.size() > 4)
    {
        for (int i = 4; i < s.card.size(); i++)
        {
            cout << "|" << left << setw(24) << s.card[i] << left << setw(23) << s.kind[i] << "|" << left << setw(48) << " " << "|" << endl;
        }
    }
    cout << "+================================================+" << "================================================+\n";

    while (1)
    {
        cout << "Which action do you want to play" << endl;
        cin >> r;
        if (r > 0 && r < 5)
        {
            break;
        }
    }

    return r;
}

int ConsoleView::print_maneuver()
{
    int a;
    cout << "MANEUVER : " << endl;
    while (1)
    {
        cout << "1 = Move 2 = Discarding Cards 3 = none" << endl;
        cin >> a;
        if (a > 0 && a < 4)
        {
            break;
        }
    }
    return a;
}

vector<int> ConsoleView::print_move(vector <int> cell)
{
    int b, c;
    vector <int> s;
    while (1)
    {
        for (int i = 0; i < cell.size(); i++)
        {
            cout << i << " = " << cell[i] << " ";

        }
        cout << endl;
        cin >> c;
        if (c >= 0 && c < cell.size() + 1)
        {
            break;
        }
    }
    s.emplace_back(c);
    while (1)
    {

        cout << "Do you want to moving or stay where you are 1 = moving 2 = stay" << endl;
        cin >> b;
        if (b == 1 || b == 2)
        {
            break;
        }
    }
    s.emplace_back(b);
    return s;
}

int ConsoleView::print_move_get_name(vector<string> name)
{
    int a;
    cout << "which player do you want to move" << endl;
    while (1)
    {
        for (int i = 0; i < name.size(); i++)
        {
            cout << i << " = " << name[i] << " ";

        }
        cout << endl;
        cin >> a;
        if (a >= 0 && a < name.size() + 1)
        {
            break;
        }
    }
    return a;
}

vector <int> ConsoleView::print_discarding(vector<string> card, vector<string> name)
{
    cout << "Which card do you want to discard?" << endl;
    int a, b;
    vector <int > r;
    while (1)
    {
        for (int i = 0; i < card.size(); i++)
        {
            cout << i << " = " << card[i] << " ";

        }
        cout << endl;
        cin >> a;
        if (a >= 0 && a < card.size() + 1)
        {
            break;
        }
    }
    r.emplace_back(a);
    cout << "which player should receive the boost?" << endl;
    while (1)
    {
        for (int i = 0; i < name.size(); i++)
        {
            cout << i << " = " << name[i] << " ";

        }
        cout << endl;
        cin >> b;
        if (b >= 0 && b < name.size() + 1)
        {
            break;
        }
    }
    r.emplace_back(b);
    return r;
}

int ConsoleView::print_scheme(vector<string> s)
{
    cout << "which card do you want to play?" << endl;
    int b;
    while (1)
    {
        for (int i = 0; i < s.size(); i++)
        {
            cout << i << " = " << s[i] << " ";

        }
        cout << endl;
        cin >> b;
        if (b >= 0 && b < s.size())
        {
            break;
        }
    }
    return b;
}

int ConsoleView::print_attack1(vector<string> s)
{
    int r;
    while (1)
    {
        cout << "which hero do you want to play?" << endl;
        {
            for (int i = 0; i < s.size(); i++)
            {
                cout << i << " = " << s[i] << " ";
            }
            cout << endl;
            cin >> r;
            if (r >= 0 && r < s.size())
            {
                break;
            }

        }
    }
    return r;
}

int ConsoleView::print_attack2(vector<string> s)
{
    int r;
    while (1)
    {
        cout << "which card do you want to play?" << endl;
        {
            for (int i = 0; i < s.size(); i++)
            {
                cout << i << " = " << s[i] << " ";
            }
            cout << endl;
            cin >> r;
            if (r >= 0 && r < s.size())
            {
                break;
            }

        }
    }
    return r;
}

void ConsoleView::end_of_game(string a)
{
    cout << a << "YOU WIN!!!!!!!!" << endl;
}

void ConsoleView::show_hand(vector<string> s)
{
    cout << "ENEMY HAND:" << endl;
    for (auto x : s)
    {
        cout << x << " ";
    }
    cout << endl;
}
