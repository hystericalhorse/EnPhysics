#include "ForceTest.h"
#include "Shapes\CircleShape.h"
#include "Emitters\GravitationalEmitter.h"

#include "Emitters\PointEmitter.h"
#include "Emitters\AreaEmitter.h"
#include "Emitters\DragEmitter.h"

#define POINT_FORCE

#define SCREEN_CENTER {m_width * 0.5f, m_height * 0.5f}

void ForceTest::Render()
{
	m_graphics->DrawCircle(m_input->GetMousePosition(), 20, { 1, 1, 1, 1 });
	m_world->Draw(m_graphics);
}

void ForceTest::Initialize()
{
	Test::Initialize();

	//ForceEmitter* gravity_emitter = new GravitationalEmitter(200);
	//m_world->AddEmitter(gravity_emitter);

#if defined(POINT_FORCE)
	auto body = new Body(m_graphics->ScreenToWorld(SCREEN_CENTER), new CircleShape(200, { 1, 1, 1, 1.0f }, false), { 0, 0 }, 0);
	ForceEmitter* force_emitter = new PointEmitter(body, 2000);

	m_world->AddEmitter(force_emitter);
#elif defined(REVERSE_POINT_FORCE)
	auto body = new Body(m_graphics->ScreenToWorld(SCREEN_CENTER), new CircleShape(200, { 1, 1, 1, 1.0f }, false), { 0, 0 }, 0);
	ForceEmitter* force_emitter = new PointEmitter(body, -2000);

	m_world->AddEmitter(force_emitter);
#elif defined(AREA_FORCE)
	auto body = new Body(m_graphics->ScreenToWorld(SCREEN_CENTER), new CircleShape(200, { 1, 1, 1, 1.0f }, false), { 0, 0 }, 0);
	ForceEmitter* force_emitter = new AreaEmitter(body, 2000, -90);

	m_world->AddEmitter(force_emitter);
#elif defined(DRAG_FORCE)
	auto body = new Body(m_graphics->ScreenToWorld(SCREEN_CENTER), new CircleShape(200, { 1, 1, 1, 1.0f }, false), { 0, 0 }, 0);
	ForceEmitter* force_emitter = new DragEmitter(body, 0.5f);

	m_world->AddEmitter(force_emitter);
#endif
}

void ForceTest::Update()
{
	Test::Update();

	if (m_input->GetKey(key_up)) m_timescale += m_time->TimeDelta();
	if (m_input->GetKey(key_down)) m_timescale -= m_time->TimeDelta();

	m_timescale = glm::clamp(m_timescale, 0.0f, 2.0f);

	if (m_input->GetKey(SDL_SCANCODE_R)) m_timescale = 1.0f;

	if (m_input->GetKeyDown(SDL_SCANCODE_SPACE))
	{

		auto body = new Body(
			m_graphics->ScreenToWorld(m_input->GetMousePosition()),
			new CircleShape(randomf(20, 30), { randomf(), randomf(), randomf(), 1 }),
			{ 0, 0 }, randomf(100, 300)
		);

		body->hasGravity = false;
		
		m_world->AddBody(body);
	}

	if (m_input->GetMouseButton(0))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf(100, 200);
	
		auto body = new Body(
			m_graphics->ScreenToWorld(m_input->GetMousePosition()),
			new CircleShape(randomf(5, 10),{ randomf(), randomf(), randomf(), 1 }),
			velocity, randomf(1, 10), Body::Dynamic, 0.0f	
		);

		body->hasGravity = false;
		body->lifetime = random(3, 5);
	
		m_world->AddBody(body);
	}
	
	if (m_input->GetMouseButton(1))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf(50, 100);
	
		auto white = randomf();
		auto body = new Body(
			m_graphics->ScreenToWorld(m_input->GetMousePosition()),
			new CircleShape(randomf(10, 20), { 0, 0, randomf(), 1 }),
			velocity, randomf(10, 20)
		);

		body->lifetime = random(3, 5);
		body->hasGravity = false;
	
		m_world->AddBody(body);
	}

	for (auto& body : m_world->GetBodies())
	{
		if (body->lifetime < 0)
		{
			m_world->RemoveBody(body);
			delete body;
		}
	}
}

void ForceTest::FixedUpdate()
{
	m_world->Step(m_time->FixedTimeDelta(), m_timescale);
}
