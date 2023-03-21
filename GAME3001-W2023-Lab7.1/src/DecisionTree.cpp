#include "DecisionTree.h"

#include <iostream>

#include "ActionNode.h"
#include "AttackAction.h"
#include "MoveToPlayerAction.h"
#include "MoveToLOSAction.h"
#include "PatrolAction.h"
DecisionTree::DecisionTree()
{
	m_buildtree();
}

DecisionTree::DecisionTree(Agent* agent)
{
	m_agent = agent;
	m_buildtree();
}

DecisionTree::~DecisionTree()
= default;

Agent* DecisionTree::GetAgent() const
{
	return m_agent;
}

void DecisionTree::SetAgent(Agent* agent)
{
	m_agent = agent;
}

LOSCondition* DecisionTree::GetLOSNode() const
{
	return m_LOSNode;
}

RadiusCondition* DecisionTree::GetRadiusNode() const
{
	return m_RadiusNode;
}

CloseCombatCondition* DecisionTree::GetCloseCombatNode() const
{
	return m_closeCombatNode;
}

TreeNode* DecisionTree::AddNode(TreeNode* parent, TreeNode* child_node, TreeNodeType type)
{
	switch (type)
	{
	case TreeNodeType::LEFT_TREE_NODE:
		parent->m_pLeft = child_node;
		break;
	case TreeNodeType::RIGHT_TREE_NODE:
		parent->m_pRight = child_node;
		break;
	}
	child_node->m_pParent = parent;
	return child_node;
}

void DecisionTree::Display() const
{
	std::cout << "decision tree nodes:" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	for(const auto node : m_treeNodeList)
	{
		std::cout << node->m_name << std::endl;
	}
}

void DecisionTree::Update()
{
}

void DecisionTree::Clean()
{
	for (auto node : m_treeNodeList)
	{
		delete node;
		node = nullptr;
	}
	m_treeNodeList.clear();
	m_treeNodeList.shrink_to_fit();

	m_LOSNode = nullptr;
	m_RadiusNode = nullptr;
	m_CloseCombatNode = nullptr;
}

void DecisionTree::MakeDecision() const
{
	TreeNode* current_node = m_treeNodeList[0]; // root node

	//traverse the tree down through each decision
	while (!current_node->m_isLeaf)
	{
		current_node = dynamic_cast<ConditionNode*>(current_node)->Condition() ?
			(current_node->m_pRight) : (current_node->m_pLeft);
	}
	// take Action
	dynamic_cast<ActionNode*>(current_node)->Action();
}

void DecisionTree::m_buildtree()
{
	// condition

	//create and add the root node
	m_LOSNode = new LOSCondition;
	m_treeNodeList.push_back(m_LOSNode);

	m_RadiusNode = new RadiusCondition();
	AddNode(m_LOSNode, m_RadiusNode,TreeNodeType::LEFT_TREE_NODE);
	m_treeNodeList.push_back(m_RadiusNode);

	m_CloseCombatNode = new CloseCombatCondition();
	AddNode(m_LOSNode, m_CloseCombatNode, TreeNodeType::RIGHT_TREE_NODE);
	m_treeNodeList.push_back(m_CloseCombatNode);

	//actions

	//left sub-tree
	TreeNode* patrolNode = AddNode(m_RadiusNode, new PatrolAction(), TreeNodeType::LEFT_TREE_NODE);
	dynamic_cast<ActionNode*>(patrolNode)->SetAgent(m_agent);
	m_treeNodeList.push_back(patrolNode);


	TreeNode* moveToLOSNode = AddNode(m_RadiusNode, new MoveToLOSAction(), TreeNodeType::RIGHT_TREE_NODE);
	dynamic_cast<ActionNode*>(moveToLOSNode)->SetAgent(m_agent);
	m_treeNodeList.push_back(moveToLOSNode);

	// right sub
	TreeNode* MovetoPlayerNode = AddNode(m_CloseCombatNode, new MoveToPlayerAction(), TreeNodeType::LEFT_TREE_NODE);
	dynamic_cast<ActionNode*>(MovetoPlayerNode)->SetAgent(m_agent);
	m_treeNodeList.push_back(MovetoPlayerNode);

	TreeNode* attackNode = AddNode(m_CloseCombatNode, new AttackAction(), TreeNodeType::RIGHT_TREE_NODE);
	dynamic_cast<ActionNode*>(attackNode)->SetAgent(m_agent);
	m_treeNodeList.push_back(attackNode);

}
