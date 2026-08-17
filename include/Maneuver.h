#pragma once
#include "Action.h"
class Maneuver : public Action
{
public:
	Maneuver(Graphics& view);
	void do_maneuver(PlayerInformation& players);
};

