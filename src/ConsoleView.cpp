#include "ConsoleView.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

bool ConsoleView::just_numeric_input(string input)
{
    try
    {
        size_t last_index;
        int to_number = stoi(input, &last_index);

        if (last_index == input.length())
            return true;
        else
        {
            cerr << "Invalid input! The number you entered contains letters and symbols...Try Again\n";
            return false;
        }
    }
    catch (const exception& e)
    {
        cerr << "Invalid input! Please enter numbers only...Try Again\n";
        return false;
    }
}

void ConsoleView::print_error(string what)
{
    cout << what << endl;
}

void ConsoleView::print_map(vector<string> text)
{
    cout << "+===========================================================================================+\n";
    cout << "|     [MAP]      *DR : Dracula *SH : Sherlock Holmes *DW : DR.Watson *S1,S2,S3 : Sisters    |\n";
    cout << "+===========================================================================================+\n";
    cout << "\033[38;2;173;216;230m(" << text[1] << ")\033[0m-\033[38;2;173;216;230m(" << text[2] << ")\033[0m      \033[38;2;139;69;19m(" << text[3] << ")\033[0m------\033[38;2;139;69;19m(" << text[4] << ")\033[0m      \033[38;2;255;220;170m(" << text[5] << ")\033[0m------\033[38;2;255;220;170m(" << text[6] << ")\033[0m" << endl;
    cout << "  |      \\    /    \\    /    \\    /    \\" << endl;
    cout << "\033[38;2;173;216;230m(" << text[7] << ")\033[0m-\033[38;2;173;216;230m(" << text[8] << ")\033[0m \033[38;2;139;69;19m(\033[0m\033[38;2;173;216;230m" << text[9] << "\033[0m\033[38;2;139;69;19m)\033[0m      \033[38;2;139;69;19m(" << text[10] << ")\033[0m------\033[38;2;139;69;19m(\033[0m\033[38;2;255;220;170m" << text[11] << "\033[0m\033[32m)\033[0m------\033[38;2;255;220;170m(" << text[12] << ")\033[0m" << endl;
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
    string temporary_input;
    int a;
    while (1)
    {
        do
        {
            cout << "1 = PLAY GAME 2 = HELP 3 = EXIT" << endl;
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));
        a = stoi(temporary_input);
        if (a > 0 && a < 4)
        {
            break;
        }
    }
    return a;
}

bool ConsoleView::print_ability(int a)
{
    if (a == 1)
    {
        while (1)
        {
            string temporary_input;
            int a;
            do
            {
                cout << "Do you want to use Dracula's ability? 1 = yes 0 = no" << endl;
                cin >> temporary_input;
            } while (!just_numeric_input(temporary_input));
            a = stoi(temporary_input);
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
    else if (a == 2)
    {
        cout << "There is no hero next to Dracula. He can't use his ability\n";
        return 0;
    }

    return 0;

}

int ConsoleView::print_complet_needs(int c, vector<int> a, vector<string> b)
{
    switch (c)
    {
    case 1:
    {
        string temporary_input;
        int s;
        while (1)
        {
            do
            {
                cout << "Enter the number of the cell where you want sister to return :" << endl;
                cout << "You must choose a cell in dracula's zone" << endl;
                cin >> temporary_input;
            } while (!just_numeric_input(temporary_input));
            s = stoi(temporary_input);
            if (s > 0 && s < 33)
            {
                break;
            }
        }
        return s;
    }
    case 2:
    {
        string temporary_input;
        int s;
        while (1)
        {
            do
            {
                cout << "Enter the number of the cell where you want Dracula to be placed:" << endl;
                cin >> temporary_input;
            } while (!just_numeric_input(temporary_input));
            s = stoi(temporary_input);
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
        string temporary_input;
        int s;
        while (1)
        {
            do
            {
                cout << "Enter the number of the cell where you want Dracula to be placed:" << endl;
                for (int i = 0; i < a.size(); i++)
                {
                    cout << i << " = " << a[i] << " ";
                }
                cout << endl;
                cin >> temporary_input;
            } while (!just_numeric_input(temporary_input));
            s = stoi(temporary_input);
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
    case 7:
    {
        string temporary_input;
        int s;
        do
        {
            cout << "Enter number : " << endl;
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));
        s = stoi(temporary_input);
        return s;
    }
    case 8:
    {
        string temporary_input;
        int s;
        while (1)
        {
            do
            {
                cout << "Select the hero you want to target:" << endl;
                for (int i = 0; i < b.size(); i++)
                {
                    cout << i << " = " << b[i] << " ";

                }
                cout << endl;
                cin >> temporary_input;
            } while (!just_numeric_input(temporary_input));
            s = stoi(temporary_input);
            if (s >= 0 && s < b.size() + 1)
            {
                break;
            }

        }
        return s;
    }
    case 9:
    {
        string temporary_input;
        int s;
        while (1)
        {
            do
            {
                cout << "Enter the number of the cell where you want Dr.Watson to be placed:" << endl;
                for (int i = 0; i < a.size(); i++)
                {
                    cout << i << " = " << a[i] << " ";
                }
                cout << endl;
                cin >> temporary_input;
            } while (!just_numeric_input(temporary_input));
            s = stoi(temporary_input);
            if (s >= 0 && s < a.size())
            {
                break;
            }
        }
        return a[s];
    }
    case 10:
    {
        cout << "You must move the Dracula 3 cells" << endl;
        return 0;
    }
    }

    return 0;
}

vector<string> ConsoleView::get_name()
{
    vector <string> name;
    int age1, age2;
    string name1, name2;
    int choice;
    for (size_t i = 1; i <= 2; i++)
    {
        cout << "Please enter the name of the player" << i << ": ";
        if (i == 1)
            cin >> name1;
        else
            cin >> name2;

        string temporary_input;
        do
        {
            cout << "Please enter the age of the player" << i << ": ";
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));

        if (i == 1)
            age1 = stoi(temporary_input);
        else
            age2 = stoi(temporary_input);
    }
    string younger;
    if (age2 < age1)
    {
        name.emplace_back(name2);
        name.emplace_back(name1);
        younger = name2;
    }
    else
    {
        name.emplace_back(name1);
        name.emplace_back(name2);
        younger = name1;
    }
    cout << younger << " is younger, so starts first-->\n";
    while (1)
    {
        string temporary_input;
        do
        {
            cout << younger << " Which one do you choose? 1 = DRACULA 2 = SHERLOCK" << endl;
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));
        choice = stoi(temporary_input);
        if (choice > 0 && choice < 3)
        {
            if (choice == 1)
                cout << "Player1's hero is DRACULA and Player2's hero is SHERLOCK\n";
            else
                cout << "Player1's hero is SHERLOCK and Player2's hero is DRACULA\n";
            cout << "Determine the position of your Sidekicks\n";
            break;
        }
    }
    name.emplace_back(to_string(choice));
    return name;
}

void ConsoleView::print_name(string name)
{
    cout << name << endl;
}

int ConsoleView::print_initial_position(string name)
{
    string temporary_input;
    int initial_position;
    while (1)
    {
        do
        {
            cout << "Enter the initial position of " << name << endl;
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));
        initial_position = stoi(temporary_input);
        if (initial_position > 0 && initial_position < 33)
        {
            break;
        }
    }
    return initial_position;
}

void ConsoleView::print_hand_cards(vector <string> card)
{
    cout << "SHOW-HAND" << endl;
    for (auto x : card)
    {
        cout << " " << x << " /";
    }
    cout << endl;
}

int ConsoleView::print_action_menu(ShowActionMenu s)
{
    int num = 3;
    if (s.attack)
    {
        num++;
    }
    if (s.scheme)
    {
        num++;
    }
    if (s.card.size() < num)
    {
        for (int i = s.card.size() - 1; i < num; i++)
        {
            s.card.emplace_back(" ");
            s.kind.emplace_back(" ");
            s.nameOfDoer.emplace_back(" ");
        }
    }
    cout << "+===========================================================================================+\n";
    cout << "|" << "PLAYER: " << left << setw(83) << s.name << "|" << endl;
    cout << "+===========================================================================================+\n";
    for (int i = 0; i < s.nameOfHero.size(); i++)
    {
        cout << "|" << left << setw(10) << s.nameOfHero[i] << " * Health:" << left << setw(2) << s.health[i] << " * Move : " << left << setw(2) << s.move[i] << " * CellNumber : " << s.cell[i] << endl;
    }
    for (int i = 0; i < s.nameofEnemy.size(); i++)
    {
        cout << "\033[91m|" << left << setw(10) << s.nameofEnemy[i] << " * Health:" << s.healthEnemy[i] << "\033[0m" << endl;
    }
    print_map(s.text);
    cout << "+=======================================================================+===================+\n";
    cout << "|                              [HAND]                                   |      [ACTION]     |\n";
    cout << "+=======================================================================+===================+\n";
    cout << "|" << left << setw(39) << s.card[0] << left << setw(20) << s.kind[0] << left << setw(12) << s.nameOfDoer[0] << "|" << left << setw(19) << "1 = Exit" << "|" << endl;
    cout << "|" << left << setw(39) << s.card[1] << left << setw(20) << s.kind[1] << left << setw(12) << s.nameOfDoer[1] << "|" << left << setw(19) << "2 = Clear Page" << "|" << endl;
    cout << "|" << left << setw(39) << s.card[2] << left << setw(20) << s.kind[2] << left << setw(12) << s.nameOfDoer[2] << "|" << left << setw(19) << "3 = Maneuver" << "|" << endl;
    int m = 3;
    if (s.scheme)
    {
        cout << "|" << left << setw(39) << s.card[m] << left << setw(20) << s.kind[m] << left << setw(12) << s.nameOfDoer[m] << "|" << left << setw(1) << m + 1 << left << setw(18) << " = Scheme" << "|" << endl;
        m++;
    }
    if (s.attack)
    {
        cout << "|" << left << setw(39) << s.card[m] << left << setw(20) << s.kind[m] << left << setw(12) << s.nameOfDoer[m] << "|" << left << setw(1) << m + 1 << left << setw(18) << " = Attack" << "|" << endl;
    }

    if (s.card.size() > num)
    {
        for (int i = num; i < s.card.size(); i++)
        {
            cout << "|" << left << setw(39) << s.card[i] << left << setw(20) << s.kind[i] << left << setw(12) << s.nameOfDoer[i] << "|" << left << setw(19) << " " << "|" << endl;
        }
    }
    cout << "+=======================================================================+===================+\n";
    if (!s.scheme)
    {
        cout << "\033[91mSCHEME UNAVAILAVLE- " << s.schemeReason << "\033[0m" << endl;
    }
    if (!s.attack)
    {
        cout << "\033[91mATTACK UNAVAILAVLE- " << s.attackReason << "\033[0m" << endl;
    }
    string temporary_input;
    int r;
    while (1)
    {
        do
        {
            cout << "Which action do you want to play" << endl;
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));
        r = stoi(temporary_input);
        if (r > 0 && r < num + 1)
        {
            break;
        }
    }

    return r;
}

int ConsoleView::print_maneuver()
{
    string temporary_input;
    int a;
    cout << "MANEUVER : " << endl;
    while (1)
    {
        do
        {
            cout << "1 = Move 2 = Discarding Cards 3 = none" << endl;
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));
        a = stoi(temporary_input);
        if (a > 0 && a < 4)
        {
            break;
        }
    }
    return a;
}

int ConsoleView::print_move1(vector <int> cell)
{
    cout << "Which house are you going to? 0 = End of move" << endl;
    int c;
    string temporary_input;
    while (1)
    {
        do
        {
            for (int i = 0; i < cell.size(); i++)
            {
                cout << i + 1 << " = " << cell[i] << " ";

            }
            cout << endl;
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));
        c = stoi(temporary_input);
        if (c >= 0 && c < cell.size() + 1)
        {
            break;
        }
    }
    return c;
}

void ConsoleView::print_move2(int a)
{
    if (a == 1)
    {
        cout << "Your ally is in this cell.You can't stay here." << endl;
    }
    if (a == 2)
    {
        cout << "You've run out of moves" << endl;
    }
    if (a == 3)
    {
        cout << "You must continue your move" << endl;
    }
}

int ConsoleView::print_move_get_name(vector<string> name)
{
    int a;
    string temporary_input;
    cout << "which player do you want to move" << endl;
    while (1)
    {
        do
        {
            for (int i = 0; i < name.size(); i++)
            {
                cout << i << " = " << name[i] << " ";
            }
            cout << endl;
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));
        a = stoi(temporary_input);
        if (a >= 0 && a < name.size() + 1)
        {
            break;
        }
    }
    return a;
}

int ConsoleView::print_discarding(vector<string> card)
{
    int r;
    string temporary_input;
    while (1)
    {
        do
        {
            cout << "Which card do you want to discard? 0 = none" << endl;
            for (int i = 0; i < card.size(); i++)
            {
                cout << i + 1 << " = " << card[i] << " ";

            }
            cout << endl;
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));
        r = stoi(temporary_input);
        if (r >= 0 && r < card.size() + 1)
        {
            break;
        }
    }
    return r;
}

int ConsoleView::print_scheme(vector<string> s)
{
    cout << "which card do you want to play?" << endl;
    int b;
    string temporary_input;
    while (1)
    {
        do
        {
            for (int i = 0; i < s.size(); i++)
            {
                cout << i << " = " << s[i] << " ";

            }
            cout << endl;
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));
        b = stoi(temporary_input);
        if (b >= 0 && b < s.size())
        {
            break;
        }
    }
    return b;
}

int ConsoleView::print_attack1(vector<string> s, int a)
{
    int r;
    string temporary_input;
    while (1)
    {
        do
        {
            if (a == 1)
            {
                cout << "which hero do you want to fight with?" << endl;
            }
            else
            {
                cout << "which hero do you want to attack?" << endl;
            }
            for (int i = 0; i < s.size(); i++)
            {
                cout << i << " = " << s[i] << " ";
            }
            cout << endl;
            cin >> temporary_input;
        } while (!just_numeric_input(temporary_input));
        r = stoi(temporary_input);
        if (r >= 0 && r < s.size())
        {
            break;
        }
    }
    return r;

}

int ConsoleView::print_attack2(vector<string> s, int a)
{
    if (a == 1)
    {
        int r;
        string temporary_input;
        while (1)
        {
            do
            {
                cout << "which card do you want to play for attack?" << endl;
                for (int i = 0; i < s.size(); i++)
                {
                    cout << i << " = " << s[i] << " ";
                }
                cout << endl;
                cin >> temporary_input;
            } while (!just_numeric_input(temporary_input));
            r = stoi(temporary_input);
            if (r >= 0 && r < s.size())
            {
                break;
            }
        }
        return r;
    }
    else if (a == 2)
    {
        int r;
        string temporary_input;
        while (1)
        {
            do
            {
                cout << "which card do you want to play for defense? 0 = none" << endl;
                for (int i = 0; i < s.size(); i++)
                {
                    cout << i + 1 << " = " << s[i] << " ";
                }
                cout << endl;
                cin >> temporary_input;
            } while (!just_numeric_input(temporary_input));
            r = stoi(temporary_input);
            if (r >= 0 && r < s.size() + 1)
            {
                break;
            }
        }
        return r;
    }
    else if (a == 3)
    {
        int r;
        string temporary_input;
        while (1)
        {
            do
            {
                cout << "which card do you want to play for?" << endl;
                for (int i = 0; i < s.size(); i++)
                {
                    cout << i << " = " << s[i] << " ";
                }
                cout << endl;
                cin >> temporary_input;
            } while (!just_numeric_input(temporary_input));
            r = stoi(temporary_input);
            if (r >= 0 && r < s.size())
            {
                break;
            }
        }
        return r;
    }

}

void ConsoleView::print_error_attack(int a)
{
    if (a == 1)
    {
        cout << "This hero cannot access the other characters. Please select another hero" << endl;
    }
    if (a == 2)
    {
        cout << "This hero has no active card. Please select another hero" << endl;
    }
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

void ConsoleView::print_combat_result(int a, int attack)
{
    if (a == 1)
    {
        cout << "Attack successful ! Damage to enemy : " << attack << endl;
    }
    if (a == 2)
    {
        cout << "Defense successful !" << endl;
    }
}

void ConsoleView::print_movenumber(int a)
{
    cout << "Allowed moves : " << a << endl;
}

void ConsoleView::clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif 
}
