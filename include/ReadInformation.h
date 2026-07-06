#pragma once
#include <fstream>
#include <vector>
#include "Cell.h"
#include "Card.h"
using namespace std;
class ReadInformation
{
private:
	vector <string> read_data_cell();
	vector <string> read_data_card(int a);
public:
	vector <Card> get_card(int a); //a=1 sherlock a=2 dracula
	vector <Cell> get_cell();
};

