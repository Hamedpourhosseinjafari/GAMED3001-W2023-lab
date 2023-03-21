#include "AttackAction.h"
#include <iostream>

AttackAction::PatrolAction()
{
	m_name = "patrol Action";
}Attack
AttackAction::~AttackAction()
= default;

void PatrolAction::Action()
{
	if (GetAgent()->GetActionState() != ActionState::PATROL)
	{
		std::cout << "performing" << m_name << std::endl;
		GetAgent()->SetActionState(ActionState::PATROL);
	}
}
