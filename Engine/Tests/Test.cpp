#include "Test.h"

Test::Test()
{
	//
}

Test::~Test()
{
	if (m_world) delete m_world;

	if (m_time) delete m_time;
	if (m_input) delete m_input;
	if (m_graphics) delete m_graphics;
}

void Test::Initialize()
{
	m_graphics = new Graphics();
	m_graphics->CreateWindow("EnPhysics", (size_t) m_width, (size_t) m_height, 800);
	m_input = new Input();
	m_time = new Time();

	seedRandom((int)time(0));
	m_time->SetFixedTimeDelta(static_cast<float> (1) / 60);

	m_world = new World();
}

void Test::Run()
{
	Update();
	m_fixed_time += m_time->TimeDelta();
	while (m_fixed_time > m_time->FixedTimeDelta())
	{
		FixedUpdate();
		m_fixed_time -= m_time->FixedTimeDelta();
	}

	//

	PreRender();
	Render();
	PostRender();
}

void Test::PreRender()
{
	m_graphics->SetColor({ 0, 0, 0, 1 });
	m_graphics->Clear();
}

void Test::PostRender()
{
	m_graphics->Present();
}


void Test::Update()
{
	UpdateEvents();

	m_input->Update();
	m_time->Update();

	for (auto& body : m_world->GetBodies())
	{
		if (body->lifetime < 0)
		{
			m_world->RemoveBody(body);
			for (auto& joint : m_world->GetJoints())
			{
				if (joint->IsAttached(body))
				{
					m_world->RemoveJoint(joint);
					delete joint;
				}
			}

			delete body;
		}
	}
}

void Test::UpdateEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_quit = true;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_quit = true;
		}
	}
}
