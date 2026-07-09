#include "ConsoleView.h"
#include <iostream>

void ConsoleView::print_map(vector<string> text) 
{
    cout<< "\033[38;2;173;216;230m("<<text[1]<<")\033[0m-\033[38;2;173;216;230m("<<text[2]<<")\033[0m      \033[38;2;139;69;19m("<<text[3]<<")\033[0m------\033[38;2;139;69;19m("<<text[4]<<")\033[0m      \033[38;2;255;220;170m("<<text[5]<<")\033[0m------\033[38;2;255;220;170m("<<text[6]<<")\033[0m"<<endl;
    cout<< "  |      \\    /    \\    /    \\    /    \\"<<endl;
    cout<< "\033[38;2;173;216;230m("<<text[7]<<")\033[0m-\033[38;2;173;216;230m("<<text[8]<<")\033[0m-\033[38;2;139;69;19m(\033[0m\033[38;2;173;216;230m"<<text[9]<<"\033[0m\033[38;2;139;69;19m)\033[0m      \033[38;2;139;69;19m("<<text[10]<<")\033[0m------\033[38;2;139;69;19m(\033[0m\033[38;2;255;220;170m"<<text[11]<<"\033[0m\033[32m)\033[0m------\033[38;2;255;220;170m("<<text[12]<<")\033[0m"<<endl;
    cout<< "  |      \\  |                   |"<<endl;
    cout<< "\033[34m("<<text[13]<<")\033[0m-\033[34m("<<text[14]<<")\033[0m-\033[34m(\033[0m\033[38;2;173;216;230m"<<text[15]<<"\033[0m\033[34m)\033[0m           \033[32m("<<text[16]<<")\033[0m   |  \033[38;2;128;0;255m("<<text[17]<<")\033[0m"<<endl;
    cout<< "  |                     /    \\  | /    \\"<<endl;
    cout<< "\033[34m(\033[0m\033[38;2;221;160;221m"<<18<<"\033[0m\033[34m)\033[0m------\033[34m(\033[0m\033[32m"<<text[19]<<"\033[0m\033[34m)\033[0m------\033[32m("<<text[20]<<")\033[0m      \033[32m(\033[0m\033[38;2;128;0;255m"<<text[21]<<"\033[0m\033[32m)\033[0m-\033[38;2;128;0;255m("<<text[22]<<")\033[0m-\033[38;2;128;0;255m("<<text[23]<<")\033[0m"<<endl;
    cout<< "  |                /         /    \\         \\"<<endl;
    cout<< "  |            \033[32m(\033[0m\033[38;2;221;160;221m"<<text[24]<<"\033[0m\033[32m)\033[0m------\033[38;2;221;160;221m("<<text[25]<<")\033[0m------\033[38;2;221;160;221m("<<text[26]<<")\033[0m------\033[38;2;128;0;255m(\033[0m\033[38;2;221;160;221m"<<text[27]<<"\033[0m\033[38;2;128;0;255m)\033[0m"<<endl;
    cout<< "  |           /    \\    /              \\    /"<<endl;
    cout<< "\033[38;2;221;160;221m("<<text[28]<<")\033[0m-\033[38;2;221;160;221m("<<text[29]<<")\033[0m-\033[38;2;221;160;221m("<<text[30]<<")\033[0m------\033[38;2;221;160;221m("<<text[31]<<")\033[0m                \033[38;2;221;160;221m("<<text[32]<<")\033[0m"<<endl<<endl;
    cout<< "cells 1, 6, 16, and 28 are secret passages\n";
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