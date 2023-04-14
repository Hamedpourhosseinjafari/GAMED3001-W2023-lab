#pragma once
#ifndef __RANGE_COMBAT_ENEMY__
#define __RANGE_COMBAT_ENEMY__

#include "Agent.h"
#include "DecisionTree.h"

class RangedCombatEnemy : public Agent
{
public:
	// Constructor Function
	RangedCombatEnemy();

	// Destructor Function
	~RangedCombatEnemy();

	// LifeCycle Functions
	void Draw() override;
	void Update() override;
	void Clean() override;

	// getters and setters (accessors and mutators)
	[[nodiscard]] float GetMaxSpeed() const;
	[[nodiscard]] float GetTurnRate() const;
	[[nodiscard]] float GetAccelerationRate() const;
	[[nodiscard]] glm::vec2 GetDesiredVelocity() const;

	void SetMaxSpeed(float speed);
	void SetTurnRate(float angle);
	void SetAccelerationRate(float rate);
	void SetDesiredVelocity(glm::vec2 target_position);

	// public functions
	void Seek();
	void LookWhereYoureGoing(glm::vec2 target_direction);
	void Reset();

	// new for lab 7.2
	void Patrol() override;
	void MoveToRange() override;
	

	// new for lab 7.3
	void Flee() override;
	void MoveToLOS() override;
	void MoveToCover() override;
	void WaitBehindCover() override;;
	void Attack() override;
	// get reference to tree
	[[nodiscard]] DecisionTree* GetTree() const;

private:
	// private movement variables
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	glm::vec2 m_startPosition;

	// where we want to go
	glm::vec2 m_desiredVelocity;

	// private function
	void m_move();

	// New for Lab 7.1
	std::vector<glm::vec2> m_patrolPath;
	int m_wayPoint;
	void m_buildPatrolPath();

	// new 7.2
	DecisionTree* m_tree;
	void m_buildTree();

};

#endif /* defined (CLOSE_COMBAT_ENEMY)*/

