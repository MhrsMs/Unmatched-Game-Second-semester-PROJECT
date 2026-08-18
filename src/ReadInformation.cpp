#include "ReadInformation.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;
vector <string> ReadInformation::read_data_cell()
{
	vector <string> s;
	ifstream file("../cell.txt");
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
	ifstream file("../card.txt");
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
			if (line.rfind("26", 0) == 0)
			{
				break;
			}
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
	if (a == 3)
	{
		bool start = false;
		while (getline(file, line))
		{

			if (!start)
			{
				if (line.rfind("26", 0) == 0)
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
		string card_photo;
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
		ss >> id >> card_photo >> attack_or_defense >> name_of_attacker
			>> effect_time >> boost >> number >> kind_of_action >> need_location
			>> need_optional_card >> need_number >> need_team_person >> need_target_person >> need_winner;
		Needs needs;
		needs.need_location = need_location;
		needs.need_number = need_number;
		needs.need_optional_card = need_optional_card;
		needs.need_target_person = need_target_person;
		needs.need_team_person = need_team_person;
		needs.need_winner = need_winner;
		Card c(id, card_photo, attack_or_defense, name_of_attacker, effect_time, boost, number, kind_of_action, needs);
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
	Cell b(0, l, k, 0, 0, 0);
	main.push_back(b);
	for (auto x : s)
	{
		stringstream ss(x);
		int number_of_cell;
		vector <string> zone;
		bool passage;
		string z1, z2, z3;
		int a1, a2, a3, a4, a5, a6;
		float x0, y0;
		vector <int> adjacent_cell;
		ss >> number_of_cell >> passage >> z1 >> z2 >> z3 >> a1 >> a2 >> a3 >> a4 >> a5 >> a6 >> x0 >> y0;
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
		Cell c(number_of_cell, zone, adjacent_cell, passage, x0, y0);
		main.emplace_back(c);
	}
	return main;
}

void ReadInformation::save_data(int a, writingData data1, writingData data2)
{
	ofstream file("../save" + to_string(a) + ".txt", ios::trunc);
	if (!file)
	{
		throw runtime_error("File did not open. ");
	}
	int line = 1;
	file << line << " " << data1.effect << " " << data1.which << endl;
	++line;
	for (auto& x : data1.players_info)
	{
		file << line << " " << x << endl;
		++line;
	}
	line = 7;
	file << line << " ";
	for (auto& x : data1.hand)
	{
		file << " " << x;
	}
	file << endl;
	++line;
	file << line << " ";
	for (auto& x : data1.null)
	{
		file << " " << x;
	}
	file << endl;
	++line;
	file << line << " " << data2.effect << " " << data2.which << endl;
	++line;
	for (auto& x : data2.players_info)
	{
		file << line << " " << x << endl;
		++line;
	}
	line = 15;
	file << line << " ";
	for (auto& x : data2.hand)
	{
		file << " " << x;
	}
	file << endl;
	++line;
	file << line << " ";
	for (auto& x : data2.null)
	{
		file << " " << x;
	}
	++line;
	file << endl;
	file << line << " " << data1.fog[0] << " " << data1.fog[1] << " " << data1.fog[2] << endl;
	++line;
	file << line << " " << getTimeAndDay() << endl;
	file.close();
}

readingData ReadInformation::read_data(int a)
{
	ifstream file("../save" + to_string(a) + ".txt");
	if (!file)
	{
		throw runtime_error("File did not open. ");
	}
	readingData data;
	string line;
	while (getline(file, line))
	{
		int linenumber;
		stringstream ss(line);
		ss >> linenumber;
		if (linenumber == 1)
		{
			int line1;
			int which1;
			int effect1;
			stringstream ss(line);
			ss >> line1 >> effect1 >> which1;
			data.which1 = which1;
			data.effect1 = effect1;
			continue;
		}
		if (linenumber == 2 || linenumber == 3 || linenumber == 4 || linenumber == 5 || linenumber == 6)
		{
			int line2;
			string name;
			int hp;
			int position;
			stringstream ss(line);
			ss >> line2 >> name >> hp >> position;
			heroData hero;
			hero.name = name;
			hero.hp = hp;
			hero.position = position;
			data.players_info1.emplace_back(hero);
			cout << hero.name << endl;
			continue;
		}
		if (linenumber == 7)
		{
			stringstream ss(line);
			int x;
			int line1;
			ss >> line1;
			while (ss >> x)
			{
				data.hand1.emplace_back(x);
			}
			continue;
		}
		if (linenumber == 8)
		{
			stringstream ss(line);
			int x;
			int line;
			ss >> line;
			while (ss >> x)
			{
				data.null1.emplace_back(x);
			}
			continue;
		}
		if (linenumber == 9)
		{
			int line2;
			int effect2;
			int which2;
			stringstream ss(line);
			ss >> line >> effect2 >> which2;
			data.which2 = which2;
			data.effect2 = effect2;
			continue;
		}
		if (linenumber == 10 || linenumber == 11 || linenumber == 12 || linenumber == 13 || linenumber == 14)
		{
			int line1;
			string name;
			int hp;
			int position;
			stringstream ss(line);
			ss >> line1 >> name >> hp >> position;
			heroData hero;
			hero.name = name;
			hero.hp = hp;
			hero.position = position;
			data.players_info2.emplace_back(hero);
			cout << hero.name << endl;
			continue;
		}
		if (linenumber == 15)
		{
			stringstream ss(line);
			int linenum;
			ss >> linenum;
			int x;
			while (ss >> x)
			{
				data.hand2.emplace_back(x);
			}
			continue;
		}
		if (linenumber == 16)
		{
			stringstream ss(line);
			int linenum;
			ss >> linenum;
			int x;
			while (ss >> x)
			{
				data.null2.emplace_back(x);
			}
			continue;
		}
		if (linenumber == 17)
		{
			stringstream ss(line);
			int f0, f1, f2, line1;
			while (ss >> line1 >> f0 >> f1 >> f2)
			{
				if (f0 != 0)
				{
					data.fog.emplace_back(f0);
					data.fog.emplace_back(f1);
					data.fog.emplace_back(f2);
				}
			}
			continue;
		}
	}
	file.close();
	return data;
}

vector<string> ReadInformation::ckeck()
{
	vector <string> c;
	ifstream file1("../save1.txt");
	string line1;
	bool found1 = false;
	while (getline(file1, line1))
	{
		stringstream ss(line1);
		int linenum;
		ss >> linenum;
		if (linenum == 18)
		{
			string hour, date;
			ss >> hour >> date;
			c.emplace_back(hour + " " + date);
			found1 = true;
			break;
		}
	}
	if (!found1)
	{
		c.emplace_back("0");
	}
	ifstream file2("../save2.txt");
	string line2;
	bool found2 = false;
	while (getline(file2, line2))
	{
		stringstream ss(line2);
		int linenum;
		ss >> linenum;
		if (linenum == 18)
		{
			string hour, date;
			ss >> hour >> date;
			c.emplace_back(hour + " " + date);
			found2 = true;
			break;
		}
	}
	if (!found2)
	{
		c.emplace_back("0");
	}
	ifstream file3("../save3.txt");
	string line3;
	bool found3 = false;
	while (getline(file3, line3))
	{
		stringstream ss(line3);
		int linenum;
		ss >> linenum;
		if (linenum == 18)
		{
			string hour, date;
			ss >> hour >> date;
			c.emplace_back(hour + " " + date);
			found3 = true;
			break;
		}
	}
	if (!found3)
	{
		c.emplace_back("0");
	}
	return c;
}
string ReadInformation::getTimeAndDay()
{
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	std::tm localTime{};
	localtime_s(&localTime, &currentTime);

	int hour = localTime.tm_hour;
	int minute = localTime.tm_min;
	int day = localTime.tm_mday;
	int month = localTime.tm_mon + 1;
	int year = localTime.tm_year + 1900;
	string date = to_string(hour) + ":" + to_string(minute) + " " + to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	return date;
}
