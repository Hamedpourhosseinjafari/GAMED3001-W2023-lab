#pragma once
#ifndef __DECISION_TREE__
#define __DECISION_TREE__

#include "Agent.h"
#include "CloseCombatCondition.h"
#include "LOSCondition.h"
#include "RadiusCondition.h"
#include "TreeNode.h"
#include "TreeNodeType.h"

#include <vector>

class DecisionTree
{
public:
	// constructor(s)
	DecisionTree();
	DecisionTree(Agent* agent);
	//destructor
	~DecisionTree();
	// getters and setters
	Agent* GetAgent() const;
	void SetAgent(Agent* agent);
	//condition node getters
	LOSCondition* GetLOSNode()  const;
	RadiusCondition* GetRadiusNode()const;
	CloseCombatCondition* GetCloseCombatNode() const;

	// public utility methodes
	TreeNode* AddNode(TreeNode* parent, TreeNode* child_node, TreeNodeType type);

	//life cycle methods
	void Display() const;
	void Update();
	void Clean();

	//main public method
	void MakeDecision()const;

private:
	//private data members
	Agent* m_agent{};
	LOSCondition* m_LOSNode{};
	RadiusCondition* m_RadiusNode{};
	CloseCombatCondition* m_CloseCombatNode{};
	//tree node list
	std::vector<TreeNode*> m_treeNodeList;
	//private methods
	void m_buildtree();
};


#endif
