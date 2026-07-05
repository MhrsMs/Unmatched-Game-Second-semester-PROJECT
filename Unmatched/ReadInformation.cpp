#include "ReadInformation.h"
#include <string>
#include <sstream>
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

vector <string> ReadInformation::read_data_card()
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
	while (getline(file, line))
	{
		s.emplace_back(line);
	}
	file.close();
	return s;
}

vector<Card> ReadInformation::get_card()
{
	vector <string> s = read_data_card();
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
		Card c(); //sakht shei class
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
	for (auto x : s)
	{
		stringstream ss(x);
		int number_of_cell;
		vector <string> zone;
		bool passage;
		vector <int> adjacent_cell;
		ss >> number_of_cell >> passage >> zone[0] >> zone[1] >> zone[2] >> adjacent_cell[0] >> adjacent_cell[1] >> adjacent_cell[2] >> adjacent_cell[3] >> adjacent_cell[4] >> adjacent_cell[5];
		zone.erase(remove(zone.begin(), zone.end(), "##"), zone.end());
		adjacent_cell.erase(remove(adjacent_cell.begin(), adjacent_cell.end(), 0), adjacent_cell.end());
		Cell c(); //sakht shei class
		main.emplace_back(c);
	}
	return main;
}