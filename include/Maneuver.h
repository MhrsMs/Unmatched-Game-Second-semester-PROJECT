#pragma once
#include "Action.h"
class Maneuver : public Action
{
public:
	void do_maneuver(PlayerInformation& players);
};

