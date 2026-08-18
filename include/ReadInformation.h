#pragma once
#include <fstream>
#include <vector>
#include "Cell.h"
#include "Card.h"
using namespace std;
struct writingData
{
	int effect;
	int which;
	vector <string> players_info;
	vector <int> hand;
	vector <int> null;
	vector <int> fog = { 0,0,0 };
};
struct heroData
{
	string name;
	int hp;
	int position;
};
struct readingData
{
	int effect1;
	int which1;
	vector <heroData> players_info1;
	vector <int> hand1;
	vector <int> null1;
	int which2;
	int effect2;
	vector <heroData> players_info2;
	vector <int> hand2;
	vector <int> null2;
	vector <int> fog;
};
class ReadInformation
{
private:
	vector <string> read_data_cell();
	vector <string> read_data_card(int a);
public:
	vector <Card> get_card(int a); //a=1 sherlock a=2 dracula
	vector <Cell> get_cell();
	void save_data(int a, writingData data1, writingData data2);
	readingData read_data(int a);
	vector <string> ckeck();
	string getTimeAndDay();
};

