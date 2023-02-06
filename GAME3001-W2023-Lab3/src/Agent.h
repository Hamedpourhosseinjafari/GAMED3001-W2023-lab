#pragma once
#ifndef __AGENT__
#define __AGENT__

#include <glm/vec4.hpp>
#include "NavigationObject.h"

class Agent : public NavigationObject
{
public:
	Agent();
	~Agent();

	// Inherited via GameObject
	void Draw() override = 0;
	void Update() override = 0;
	void Clean() override = 0;

	// getters
	[[nodiscard]] glm::vec2 GetTargetPosition() const;
	[[nodiscard]] glm::vec2 GetCurrentDirection() const;
	[[nodiscard]] float GetLOSDistance() const;
	[[nodiscard]] bool HasLOS() const;
	[[nodiscard]] float GetCurrentHeading() const;
	[[nodiscard]] glm::vec4 GetLOSColour() const;

	[[nodiscard]] glm::vec2 getLeftLoseEndPoint() const;
	[[nodiscard]] glm::vec2 getLeftLeftLoseEndPoint() const;
	[[nodiscard]] glm::vec2 GetMiddleLoseEndPoint() const;
	[[nodiscard]] glm::vec2 GetRightLoseEndPoint() const;
	[[nodiscard]] glm::vec2 GetRightRightLoseEndPoint() const;
	bool* GetCollisionWhiskers();
	glm::vec4 GetLineCOlour(int index) const;
	float GetWhiskersAngle()const;



	// setters
	void SetTargetPosition(glm::vec2 new_position);
	void SetCurrentDirection(glm::vec2 new_direction);
	void SetLOSDistance(float distance);
	void SetHasLOS(bool state);
	void SetCurrentHeading(float heading);
	void SetLOSColour(glm::vec4 colour);

	void SetLeftEndPoint(glm::vec2 point);
	void SetLeftLeftEndPoint(glm::vec2 point);
	void SetMiddleEndPoint(glm::vec2 point);
	void SetRightEndPoint(glm::vec2 point);
	void SetRightRightEndPoint(glm::vec2 point);
	void SetLineColour(int index, glm::vec4 colour);
	void SetWhiskersAngle(float angle);
	//void setRightWhiskerAngle(float angle);
	//void setLeftWhiskerAngle(float angle);

	//utility function
	void UpdateWhiskers(float angle);
private:
	void ChangeDirection();
	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;

	// LOS
	float m_LOSDistance;
	bool m_hasLOS;
	glm::vec4 m_LOSColour;

	//whiskers
	glm::vec2 m_leftLoseEndPoint;
	glm::vec2 m_leftLeftLoseEndPoint;
	glm::vec2 m_middleLoseEndPoint;
	glm::vec2 m_rightLoseEndPoint;
	glm::vec2 m_rightRightLoseEndPoint;
	glm::vec4 m_lineColour[5];
	bool m_collisionWhiskers[5];
	float m_whiskerAngle;
	float m_righttightA;
	float m_lefleftA;

};



#endif /* defined ( __AGENT__) */