#include "MoveToPlayerAction.h"


#include <iostream>

MoveToPlayerAction::MoveToPlayerAction()
{
	m_name = "MoveToPlayerAction Action";
}

MoveToPlayerAction::~MoveToPlayerAction()
= default;

void MoveToPlayerAction::Action()
{
	if (GetAgent()->GetActionState() != ActionState::PATROL)
	{
		std::cout << "performing" << m_name << std::endl;
		GetAgent()->SetActionState(ActionState::PATROL);
	}
}
