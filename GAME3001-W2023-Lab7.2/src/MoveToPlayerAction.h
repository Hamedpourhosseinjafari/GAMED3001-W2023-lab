#pragma once
#ifndef __MOVE_TO_LOS_ACTION__
#define __MOVE_TO_LOS__ACTION__
#include "ActionNode.h"

class MoveToPlayerAction : public ActionNode
{
public:
	MoveToPlayerAction();
	virtual ~MoveToPlayerAction();

	virtual void Action() override; // define here
};
#endif
