#pragma once
#include <fstream>
#include <vector>
using namespace std;
class ReadInformation
{
private:
	vector <string> read_data_cell();
	vector <string> read_data_card();
public:
	vector <Card> get_card();
	vector <Cell> get_cell();
};

