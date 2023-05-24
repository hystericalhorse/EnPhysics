#include "CollisionTest.h"
#include "Object/Collision.h"
#include "Shapes\CircleShape.h"

Body* mouse;

void CollisionTest::Render()
{
	//m_graphics->DrawCircle(m_input->GetMousePosition(), 20, { 1, 1, 1, 1 });
	m_world->Draw(m_graphics);
}

void CollisionTest::Update()
{
	Test::Update();

	mouse->position = m_graphics->ScreenToWorld(m_input->GetMousePosition());

	if (m_input->GetMouseButtonDown(0))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf();

		auto body = new Body(
			m_graphics->ScreenToWorld(m_input->GetMousePosition()),
			new CircleShape(randomf(50, 69), { randomf(), randomf(), randomf(), 1 }),
			{0, 0}, randomf(1, 10)
		);

		body->damping = 1.0f;
		body->hasGravity = false;

		m_world->AddBody(body);
	}
}

void CollisionTest::FixedUpdate()
{
	m_world->Step(m_time->FixedTimeDelta());
}

void CollisionTest::Initialize()
{
	Test::Initialize();
	mouse = new Body(
		m_graphics->ScreenToWorld(m_input->GetMousePosition()),
		new CircleShape(80, { 1, 1, 1, 1 }),
		{ 0, 0 }, 1000
	);

	mouse->hasGravity = false;
	mouse->damping = 0;

	m_world->AddBody(mouse);
}