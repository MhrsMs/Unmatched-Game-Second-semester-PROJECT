#pragma once
#include "Action.h"
class Attack : public Action
{
public:
	Attack(Graphics& view);
	void do_attack(PlayerInformation & players);
	int can_attack(PlayerInformation& players);
};

