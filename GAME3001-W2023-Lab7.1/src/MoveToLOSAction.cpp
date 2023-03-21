#include "MoveToLOSAction.h"

#include <iostream>

MoveToLOSAction::MoveToLOSAction()
{
	m_name = "MOVEtoLOSaction Action";
}

MoveToLOSAction::~MoveToLOSAction()
= default;

void MoveToLOSAction::Action()
{
	if (GetAgent()->GetActionState() != ActionState::PATROL)
	{
		std::cout << "performing" << m_name << std::endl;
		GetAgent()->SetActionState(ActionState::PATROL);
	}
}
