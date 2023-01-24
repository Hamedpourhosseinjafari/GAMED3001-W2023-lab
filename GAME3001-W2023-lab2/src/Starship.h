#pragma once
#ifndef  __STARSHIP__
#define  __STARSHIP__
#include "Agent.h"
class StarShip : public Agent
{
public:
	StarShip();

	~StarShip();
	void Draw() override;
	void Update() override;
	void Clean() override;

	//getter and setter(accessors and mutators)
	float GetMaxSpeed()const;
	float GetTurnRate()const;
	float GetAccelerationRate()const;
	glm::vec2 GetDesiredVelocity() const;


	void SetMaxSpeed(float speed);
	void SetTurnRate(float angle);
	void SetAcceletaionRate(float rate);
	void SetDesiredVelocity(glm::vec2 target_position);
	//public functions
	void seek();
	void LookWhereYoureGoing(glm::vec2 target_direction);
private:
	// private movement variables
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;

	//wher we want to go
	glm::vec2 m_desiredVelocity;
	//private function
	void m_move();
};


#endif
