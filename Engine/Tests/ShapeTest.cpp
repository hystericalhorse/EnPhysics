#include "ShapeTest.h"
#include "Shapes\CircleShape.h"
#include "Shapes\RectShape.h"

void ShapeTest::Render()
{
	m_graphics->DrawCircle(m_input->GetMousePosition(), 20, { 1, 1, 1, 1 });
	m_world->Draw(m_graphics);
}

void ShapeTest::Update()
{
	Test::Update();

	if (m_input->GetMouseButton(0))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf(100, 200);

		auto body = new Body(
			m_graphics->ScreenToWorld(m_input->GetMousePosition()),
			new RectShape(randomf(20, 40), randomf(20, 40), {randomf(), randomf(), randomf(), 1}, false),
			velocity, randomf(1, 10)
		);

		body->hasGravity = true;
		body->lifetime = randomf(3, 5);

		m_world->AddBody(body);
	}

	if (m_input->GetMouseButton(1))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf(100, 200);

		auto body = new Body(
			m_graphics->ScreenToWorld(m_input->GetMousePosition()),
			new RectShape(randomf(20, 40), randomf(20, 40), { randomf(), randomf(), randomf(), 1 }),
			velocity, randomf(1, 10)
		);

		body->hasGravity = false;
		body->lifetime = randomf(1, 3);

		m_world->AddBody(body);
	}
}

void ShapeTest::FixedUpdate()
{
	m_world->Step(m_time->FixedTimeDelta());
}

void ShapeTest::Initialize()
{
	Test::Initialize();
}