#include "ReadInformation.h"
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
vector <string> ReadInformation::read_data_cell()
{
	vector <string> s;
	ifstream file("cell.txt");
	if (!file.is_open())
	{
		return {};
	}
	if (!file)
	{
		throw runtime_error("File did not open. ");
	}
	string line;
	while (getline(file, line))
	{
		s.emplace_back(line);
	}
	file.close();
	return s;
}

vector <string> ReadInformation::read_data_card(int a)
{
	vector <string> s;
	ifstream file("card.txt");
	if (!file.is_open())
	{
		return {};
	}
	if (!file)
	{
		throw runtime_error("File did not open. ");
	}
	string line;
	if (a == 2)
	{
		bool start = false;
		while (getline(file, line))
		{

			if (!start)
			{
				if (line.rfind("13", 0) == 0)
				{
					start = true;
				}
				else
				{
					continue;
				}
			}
			s.emplace_back(line);
		}

	}
	if (a == 1)
	{
		while (getline(file, line))
		{
			if (line.rfind("13", 0) == 0)
			{
				break;
			}
			s.emplace_back(line);
		}
	}

	file.close();
	return s;
}

vector<Card> ReadInformation::get_card(int a)
{
	vector <string> s = read_data_card(a);
	vector<Card> main;
	for (auto x : s)
	{
		stringstream ss(x);
		int id;
		string card_name;
		int attack_or_defense;
		string name_of_attacker;
		int effect_time;
		int boost;
		int number;
		string kind_of_action;
		bool need_location;
		bool need_optional_card;
		bool need_number;
		bool need_team_person;
		bool need_target_person;
		bool need_winner;
		ss >> id >> card_name >> attack_or_defense >> name_of_attacker
			>> effect_time >> boost >> number >> kind_of_action >> need_location
			>> need_optional_card >> need_number >> need_team_person >> need_target_person >> need_winner;
		Needs needs;
		needs.need_location = need_location;
		needs.need_number = need_number;
		needs.need_optional_card = need_optional_card;
		needs.need_target_person = need_target_person;
		needs.need_team_person = need_team_person;
		needs.need_winner = need_winner;
		Card c(id, card_name, attack_or_defense, name_of_attacker, effect_time, boost, number, kind_of_action, needs);
		for (int i = number; i > 0; i--)
		{
			main.emplace_back(c);
		}

	}
	return main;
}

vector<Cell> ReadInformation::get_cell()
{
	vector <string> s = read_data_cell();
	vector<Cell> main;
	vector <string> l = {};
	vector <int> k = {};
	Cell b(0, l, k, 0);
	main.push_back(b);
	for (auto x : s)
	{
		stringstream ss(x);
		int number_of_cell;
		vector <string> zone;
		bool passage;
		string z1, z2, z3;
		int a1, a2, a3, a4, a5, a6;
		vector <int> adjacent_cell;
		ss >> number_of_cell >> passage >> z1 >> z2 >> z3 >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
		zone.emplace_back(z1);
		zone.emplace_back(z2);
		zone.emplace_back(z3);
		adjacent_cell.emplace_back(a1);
		adjacent_cell.emplace_back(a2);
		adjacent_cell.emplace_back(a3);
		adjacent_cell.emplace_back(a4);
		adjacent_cell.emplace_back(a5);
		adjacent_cell.emplace_back(a6);
		zone.erase(remove(zone.begin(), zone.end(), "##"), zone.end());
		adjacent_cell.erase(remove(adjacent_cell.begin(), adjacent_cell.end(), 0), adjacent_cell.end());
		Cell c(number_of_cell, zone, adjacent_cell, passage);
		main.emplace_back(c);
	}
	return main;
}