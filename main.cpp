#include "GameManager.h"
int main()
{
	GameManager gm;
	try {
		gm.run();
	}
	catch (...)
	{
		cerr << "Unknown error occurred!" << endl;
	}
	return 0;
}