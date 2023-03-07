#include  "PathNode.h"
#include "util.h"

PathNode::PathNode()
{
	SetWidth(10);
	SetHeight(10);
	GetTransform()->position = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	SetType(GameObjectType::PATH_NODE);

	SetCurrentHeading(0.0f);
	SetLOSDistance(100.0f);
	SetLOSColour(glm::vec4(0.0f, 0.5f, 1.0f, 1.0f)); // ligh blue
}

PathNode::~PathNode()
= default;

void PathNode::Draw()
{
	Util::DrawRect(GetTransform()->position - glm::vec2(5.0f, 50.f), GetWidth(), GetHeight(), GetLOSColour());
}

void PathNode::Update()
{
}

void PathNode::Clean()
{
}
