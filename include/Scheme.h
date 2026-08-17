#pragma once
#include "Action.h"
class Scheme : public Action
{
public:
	Scheme(Graphics& view);
	void do_scheme(PlayerInformation& players);
	int can_scheme(PlayerInformation& players);
};

