#pragma once
#ifndef __ATTACK_ACTION__
#define __ATTACK__ACTION__
#include "ActionNode.h"

class AttackAction : public ActionNode
{
public:
	AttackAction();
	virtual ~AttackAction();

	virtual void Action() override; // define here
};
#endif
