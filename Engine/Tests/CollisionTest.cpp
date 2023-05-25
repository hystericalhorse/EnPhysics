#include "CollisionTest.h"
#include "Object\Collision.h"
#include "Shapes\CircleShape.h"
#include "Shapes\RectShape.h"

Body* mouse;

void CollisionTest::Render()
{
	//m_graphics->DrawCircle(m_input->GetMousePosition(), 20, { 1, 1, 1, 1 });
	m_world->Draw(m_graphics);
}

void CollisionTest::Update()
{
	Test::Update();

	mouse->velocity = mouse->position - m_graphics->ScreenToWorld(m_input->GetMousePosition());
	mouse->position = m_graphics->ScreenToWorld(m_input->GetMousePosition());

	if (m_input->GetMouseButtonDown(0))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf();

		auto body = new Body(
			m_graphics->ScreenToWorld(m_input->GetMousePosition()),
			new CircleShape(randomf(50, 69), { randomf(), randomf(), randomf(), 1 }),
			velocity, randomf(1, 10)
		);

		body->damping = 0.3f;
		//body->hasGravity = false;
		//body->lifetime = randomf(2, 4);

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
	mouse->restitution = 2.0f;

	m_world->AddBody(mouse);

	auto ground = new Body(
		m_graphics->ScreenToWorld({ m_width * 0.5f, m_height + 200 }),
		new CircleShape(500, { 1, 1, 1, 1 }),
		{0, 0}, randomf(1, 10), Body::Static
	);
	ground->hasGravity = false;

	m_world->AddBody(ground);
}