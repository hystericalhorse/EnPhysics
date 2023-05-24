#include "Joint.h"
#include "Engine\Graphics.h"

Joint::Joint(Body* bodyA, Body* bodyB, float stiffness, float length) :
	m_head{ bodyA }, m_tail{ bodyB }, m_length{ length }, m_stiffness{ stiffness }
{
	if (m_length == 0) m_length = glm::distance(bodyA->position, bodyB->position);
}

void Joint::Step(float deltaTime)
{
	if (IsNull()) return;

	glm::vec2 dir = m_head->position - m_tail->position;
	auto length = glm::length(dir);

	// F = -kx

	auto x = length - m_length;
	//if (x < 0) return;
	auto force = -m_stiffness * x;

	auto ndir = glm::normalize(dir);

	m_head->ApplyImpulse( force * ndir);
	m_tail->ApplyImpulse(-force * ndir);
}

void Joint::Draw(class Graphics* graphics)
{
	if (IsNull()) return;
	graphics->DrawLine(graphics->WorldToScreen(m_head->position), graphics->WorldToScreen(m_tail->position), glm::vec4{ 1.0f });
}