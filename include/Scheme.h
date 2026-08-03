#pragma once
#include "Action.h"
class Scheme : public Action
{
public:
	void do_scheme(PlayerInformation& players);
	int can_scheme(PlayerInformation& players);
};

