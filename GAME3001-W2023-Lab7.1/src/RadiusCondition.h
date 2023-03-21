
#pragma once
#ifndef __RADIUS_CONDITION__
#define __RADIUS_CONDITION__

#include "ConditionNode.h"

class RadiusCondition : public ConditionNode
{
	RadiusCondition(bool within_radius = false);
	virtual ~RadiusCondition();

	//getters and setters
	void SetIsWithinRadius(bool state);
	virtual bool Condition() override;;
private:
	bool m_isWithinRadius;
};
#endif
