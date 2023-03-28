#pragma once
#ifndef __PATROL_ACTION__
#define __PATROL__ACTION__
#include "ActionNode.h"

class PatrolAction : public ActionNode
{
public:
	PatrolAction();
	virtual ~PatrolAction();

	virtual void Action() override; // define here
};
#endif
