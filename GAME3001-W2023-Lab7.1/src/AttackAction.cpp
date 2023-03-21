#include "AttackAction.h"
#include <iostream>

AttackAction::AttackAction()
{
	m_name = "patrol Action";
}
AttackAction::~AttackAction()
= default;

void AttackAction::Action()
{
	if (GetAgent()->GetActionState() != ActionState::PATROL)
	{
		std::cout << "performing" << m_name << std::endl;
		GetAgent()->SetActionState(ActionState::PATROL);
	}
}
