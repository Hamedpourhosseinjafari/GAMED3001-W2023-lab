#include "MoveToRangedAction.h"

#include <iostream>

MoveToRangeAction::MoveToRangeAction()
{
	m_name = "Move To Player Action";
}

MoveToRangeAction::~MoveToRangeAction()
= default;

void MoveToRangeAction::Action()
{
	if(GetAgent()->GetActionState() != ActionState::MOVE_TO_RANGE)
	{
		std::cout << "Performing " << m_name << std::endl;
		GetAgent()->SetActionState(ActionState::MOVE_TO_RANGE);
	}
}