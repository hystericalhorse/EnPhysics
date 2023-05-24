#include "ParticleTest.h"
#include "Shapes\CircleShape.h"

void ParticleTest::Render()
{
	m_graphics->DrawCircle(m_input->GetMousePosition(), 20, { 1, 1, 1, 1 });
	m_world->Draw(m_graphics);
}

void ParticleTest::Update()
{
	Test::Update();

	if (m_input->GetMouseButton(0))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf(100, 200);

		auto body = new Body(
			m_graphics->ScreenToWorld(m_input->GetMousePosition()),
			new CircleShape(randomf(100, 200), { randomf(), randomf(), randomf(), 1 }),
			velocity, randomf(1, 10)
		);

		body->hasGravity = false;

		m_world->AddBody(body);
	}
}

void ParticleTest::FixedUpdate()
{
	m_world->Step(m_time->FixedTimeDelta());
}

void ParticleTest::Initialize()
{
	Test::Initialize();
}