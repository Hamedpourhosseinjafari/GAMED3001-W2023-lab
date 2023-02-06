#include "Agent.h"

#include "Util.h"

Agent::Agent()
{
	//initialize the whisker colour
	m_lineColour[0] = glm::vec4(0, 1, 0, 1);//green
	m_lineColour[1] = glm::vec4(0, 1, 0, 1);//green
	m_lineColour[2] = glm::vec4(0, 1, 0, 1);//green
	m_lineColour[3] = glm::vec4(0, 1, 0, 1);//green
	m_lineColour[4] = glm::vec4(0, 1, 0, 1);//green


	//initialize the whisker collision booleans
	m_collisionWhiskers[0] = false;
	m_collisionWhiskers[1] = false;
	m_collisionWhiskers[2] = false;
	m_collisionWhiskers[3] = false;
	m_collisionWhiskers[4] = false;

	m_whiskerAngle = 45;
}

Agent::~Agent()
= default;

glm::vec2 Agent::GetTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Agent::GetCurrentDirection() const
{
	return m_currentDirection;
}

float Agent::GetLOSDistance() const
{
	return m_LOSDistance;
}

bool Agent::HasLOS() const
{
	return m_hasLOS;
}

float Agent::GetCurrentHeading() const
{
	return m_currentHeading;
}

glm::vec4 Agent::GetLOSColour() const
{
	return m_LOSColour;
}

glm::vec2 Agent::getLeftLoseEndPoint() const
{
	return m_leftLoseEndPoint;
}

glm::vec2 Agent::getLeftLeftLoseEndPoint() const
{
	return m_leftLeftLoseEndPoint;
}

glm::vec2 Agent::GetRightRightLoseEndPoint() const
{
	return m_rightRightLoseEndPoint;
}

void Agent::SetLeftLeftEndPoint(glm::vec2 point)
{
	m_leftLeftLoseEndPoint = point;
}

void Agent::SetRightRightEndPoint(glm::vec2 point)
{
	m_rightRightLoseEndPoint = point;
}

glm::vec2 Agent::GetMiddleLoseEndPoint() const
{
	return m_middleLoseEndPoint;
}

glm::vec2 Agent::GetRightLoseEndPoint() const
{
	return m_rightLoseEndPoint;
}

bool* Agent::GetCollisionWhiskers()
{
	return m_collisionWhiskers;
}

glm::vec4 Agent::GetLineCOlour(int index) const
{
	return m_lineColour[index];
}

float Agent::GetWhiskersAngle() const
{
	return m_whiskerAngle;
}

void Agent::SetLeftEndPoint( const glm::vec2 point)
{
	m_leftLoseEndPoint = point;
}

void Agent::SetMiddleEndPoint(const glm::vec2 point)
{
	m_middleLoseEndPoint = point;
}

void Agent::SetRightEndPoint(const glm::vec2 point)
{
	m_rightLoseEndPoint = point;
}

void Agent::SetLineColour(int index, glm::vec4 colour)
{
	m_lineColour[index] = colour;
}

void Agent::SetWhiskersAngle(float angle)
{
	m_whiskerAngle = angle;
}

//void Agent::setRightWhiskerAngle(float angle)
//{
//	m_righttightA = angle;
//}
//
//void Agent::setLeftWhiskerAngle(float angle)
//{
//	m_lefleftA = angle;
//}

void Agent::UpdateWhiskers(const float angle)
{
	m_whiskerAngle = angle;

	//center //miidle whisker
	SetMiddleEndPoint(GetTransform()->position + GetCurrentDirection() * GetLOSDistance());

	//left whisker
	float x = sin((GetCurrentHeading() - m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	float y = cos((GetCurrentHeading() - m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	SetLeftEndPoint(GetTransform()->position + glm::vec2(x, -y) * GetLOSDistance() * 0.75f);

	//Left Left
	 x = sin((GetCurrentHeading() - m_whiskerAngle + 60.0f) * Util::Deg2Rad);
	 y = cos((GetCurrentHeading() - m_whiskerAngle + 60.0f) * Util::Deg2Rad);
	SetLeftLeftEndPoint(GetTransform()->position + glm::vec2(x, -y) * GetLOSDistance() * 0.75f);


	//Right whisker
	 x = sin((GetCurrentHeading() + m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	 y = cos((GetCurrentHeading() + m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	SetRightEndPoint(GetTransform()->position + glm::vec2(x, -y) * GetLOSDistance() * 0.75f);


	//Right Right
	x = sin((GetCurrentHeading() + m_whiskerAngle + 120.0f) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() + m_whiskerAngle + 120.0f) * Util::Deg2Rad);
	SetRightRightEndPoint(GetTransform()->position + glm::vec2(x, -y) * GetLOSDistance() * 0.75f);
}

void Agent::SetTargetPosition(const glm::vec2 new_position)
{
	m_targetPosition = new_position;
}

void Agent::SetCurrentDirection(const glm::vec2 new_direction)
{
	m_currentDirection = new_direction;
}

void Agent::SetLOSDistance(const float distance)
{
	m_LOSDistance = distance;
}

void Agent::SetHasLOS(const bool state)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1);
}

void Agent::SetCurrentHeading(const float heading)
{
	m_currentHeading = heading;
	ChangeDirection();
}

void Agent::SetLOSColour(const glm::vec4 colour)
{
	m_LOSColour = colour;
}

void Agent::ChangeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);
}
