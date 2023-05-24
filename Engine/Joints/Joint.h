#pragma once
#include "Object\Body.h"

class Joint
{
public:
	Joint(Body* bodyA, Body* bodyB, float stiffness = 0.0f, float length = 0.0f);

	void Step(float deltaTime);
	void Draw(class Graphics* graphics);

	bool IsNull() { return (m_head == nullptr || m_tail == nullptr); }
	bool IsAttached(Body* body) { return (m_head == body || m_tail == body); }

	void AdjustLength(float length = 1) { m_length = (length > 0) ? length : 1.0f; }

	Body* GetHead() { return m_head; }
	Body* GetTail() { return m_tail; }

protected:
	float m_length{ 0.0f };
	float m_stiffness{ 0.0f };

	Body* m_head{ nullptr };
	Body* m_tail{ nullptr };
};