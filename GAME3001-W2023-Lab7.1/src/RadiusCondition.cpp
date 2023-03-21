#include "RadiusCondition.h"

RadiusCondition::RadiusCondition(bool within_radius)
{
	m_name = "radius condition";
	SetIsWithinRadius(within_radius);
}

RadiusCondition::~RadiusCondition()
= default;

void RadiusCondition::SetIsWithinRadius(const bool state)
{
	m_isWithinRadius = state;
}

bool RadiusCondition::Condition()
{
	return m_isWithinRadius;
}
