#include "JointTest.h"
#include "Shapes\CircleShape.h"
#include "Emitters\GravitationalEmitter.h"

#include "Emitters\PointEmitter.h"
#include "Emitters\AreaEmitter.h"
#include "Emitters\DragEmitter.h"

#define SPRING_STIFFNESS 10000
#define SPRING_LENGTH 50
#define BODY_DAMPING 5

#define GRID

#define CHAIN_SIZE 4
#define GRID_HEIGHT 3

void JointTest::Render()
{
	//m_graphics->DrawCircle(m_input->GetMousePosition(), 20, { 1, 1, 1, 1 });
	m_world->Draw(m_graphics);
}

void JointTest::Initialize()
{
	Test::Initialize();

	auto body = new Body(
		m_graphics->ScreenToWorld({ m_width * 0.5f, m_height * 0.5f }),
		new CircleShape(20, { 1, 1, 1, 1.0f }, true),
		{ 0, 0 }, 0, Body::Static
	);

	body->hasGravity = false;
	m_anchor = body;
	m_world->AddBody(m_anchor);

#ifdef CHAIN
	for (size_t i = 0; i < CHAIN_SIZE; i++)
	{
		auto prevBody = body;

		body = new Body(
			m_graphics->ScreenToWorld({ m_width * 0.5f, m_height * 0.5f + i }),
			new CircleShape(20, { randomf(), randomf(), randomf(), 1 }),
			{0, 0}, randomf(20, 15), Body::Dynamic, BODY_DAMPING
		);

		body->hasGravity = false;
		m_world->AddBody(body);

		auto joint = new Joint(
			prevBody, body, SPRING_STIFFNESS, SPRING_LENGTH
		);

		m_world->AddJoint(joint);
	}
#elif defined GRID

	auto lprev = m_anchor;
	auto rprev = m_anchor;

	float hyp = sqrt(2 * (SPRING_LENGTH * SPRING_LENGTH));

	for (size_t i = 1; i <= GRID_HEIGHT; i++)
	{
		auto left = new Body(
			m_graphics->ScreenToWorld({ m_width * 0.5f - SPRING_LENGTH * i, m_height * 0.5f + SPRING_LENGTH * i }),
			new CircleShape(20, { randomf(), randomf(), randomf(), 1 }),
			{ 0, 0 }, randomf(20, 15), Body::Dynamic, BODY_DAMPING
		);
		auto right = new Body(
			m_graphics->ScreenToWorld({ m_width * 0.5f + SPRING_LENGTH * i, m_height * 0.5f + SPRING_LENGTH * i }),
			new CircleShape(20, { randomf(), randomf(), randomf(), 1 }),
			{ 0, 0 }, randomf(20, 15), Body::Dynamic, BODY_DAMPING
		);

		left->hasGravity = false;
		right->hasGravity = false;

		m_world->AddBody(left);
		m_world->AddBody(right);
	
		auto ljoint = new Joint(
			lprev, left, SPRING_STIFFNESS, SPRING_LENGTH
		);
	
		auto rjoint = new Joint(
			rprev, right, SPRING_STIFFNESS, SPRING_LENGTH
		);

		auto tlbrj = new Joint(
			lprev, right, SPRING_STIFFNESS, hyp
		);

		auto trblj = new Joint(
			rprev, left, SPRING_STIFFNESS, hyp
		);
	
		auto crossjoint = new Joint(
			left, right, SPRING_STIFFNESS, SPRING_LENGTH
		);
	
		m_world->AddJoint(ljoint);
		m_world->AddJoint(rjoint);
		m_world->AddJoint(tlbrj);
		m_world->AddJoint(trblj);
		m_world->AddJoint(crossjoint);

		lprev = left;
		rprev = right;
	}

#endif
}

void JointTest::Update()
{
	Test::Update();

	if (m_input->GetKey(key_up)) m_timescale += m_time->TimeDelta();
	if (m_input->GetKey(key_down)) m_timescale -= m_time->TimeDelta();
	
	m_timescale = glm::clamp(m_timescale, 0.0f, 2.0f);

	if (m_input->GetKey(SDL_SCANCODE_R)) m_timescale = 1.0f;

	m_anchor->position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
	if (m_input->GetMouseButtonDown(0))
	{
#ifdef CHAIN
		auto prevBody = (m_world->GetJoints().back())->GetTail();

		auto body = new Body(
			{ prevBody->position.x, prevBody->position.y + 1 },
			new CircleShape(20, { randomf(), randomf(), randomf(), 1 }),
			{ 0, 0 }, randomf(20, 15), Body::Dynamic, BODY_DAMPING
		);

		body->hasGravity = false;
		m_world->AddBody(body);

		auto joint = new Joint(
			prevBody, body, SPRING_STIFFNESS, SPRING_LENGTH
		);

		m_world->AddJoint(joint);
	
#elif defined GRID
		auto lprev = (m_world->GetJoints().back())->GetTail();
		auto rprev = (m_world->GetJoints().back())->GetHead();

		float hyp = sqrt(2 * (SPRING_LENGTH * SPRING_LENGTH));

		auto left = new Body(
			{ lprev->position.x - SPRING_LENGTH, lprev->position.y + SPRING_LENGTH },
			new CircleShape(20, { randomf(), randomf(), randomf(), 1 }),
			{ 0, 0 }, randomf(20, 15), Body::Dynamic, BODY_DAMPING
		);
		auto right = new Body(
			{ rprev->position.x + SPRING_LENGTH, rprev->position.y + SPRING_LENGTH },
			new CircleShape(20, { randomf(), randomf(), randomf(), 1 }),
			{ 0, 0 }, randomf(20, 15), Body::Dynamic, BODY_DAMPING
		);

		left->hasGravity = false;
		right->hasGravity = false;

		m_world->AddBody(left);
		m_world->AddBody(right);

		auto ljoint = new Joint(
			lprev, left, SPRING_STIFFNESS, SPRING_LENGTH
		);

		auto rjoint = new Joint(
			rprev, right, SPRING_STIFFNESS, SPRING_LENGTH
		);

		auto tlbrj = new Joint(
			lprev, right, SPRING_STIFFNESS, hyp
		);

		auto trblj = new Joint(
			rprev, left, SPRING_STIFFNESS, hyp
		);

		auto crossjoint = new Joint(
			left, right, SPRING_STIFFNESS, SPRING_LENGTH
		);

		m_world->AddJoint(ljoint);
		m_world->AddJoint(rjoint);
		m_world->AddJoint(tlbrj);
		m_world->AddJoint(trblj);
		m_world->AddJoint(crossjoint);

		lprev = left;
		rprev = right;

#endif
	}

	for (auto& body : m_world->GetBodies())
	{
		if (body == nullptr) continue;
		if (body->lifetime < 0)
		{
			m_world->RemoveBody(body);

			for (auto& joint : m_world->GetJoints())
			{
				if (joint->IsAttached(body))
				{
					m_world->RemoveJoint(joint);
					joint = nullptr;
					delete joint;
				}
			}

			body = nullptr;
			delete body;
		}
	}

	
}

void JointTest::FixedUpdate()
{
	m_world->Step(m_time->FixedTimeDelta(), m_timescale);
}