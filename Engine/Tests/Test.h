#pragma once

#include "Engine\Graphics.h"
#include "Engine\Input.h"
#include "Engine\Time.h"
#include "Math\Random.h"
#include "Object\World.h"

class Test
{
public:
	Test();
	~Test();

	virtual void Initialize();
	virtual void PreRender();
	virtual void Render() = 0;
	virtual void PostRender();
	virtual void Run();
	virtual void FixedUpdate() = 0;
	virtual void Update();

	bool IsQuit() { return m_quit; }

protected:
	void UpdateEvents();

protected:
	bool m_quit{ false };

	float m_height{ 600 };
	float m_width{ 800 };

	float m_fixed_time{ 0.0f };
	float m_timescale{ 1.0f };

	Graphics* m_graphics{ nullptr };
	Input* m_input{ nullptr };
	Time* m_time{ nullptr };

	World* m_world{ nullptr };
};

#define SCREEN_CENTER {m_width * 0.5f, m_height * 0.5f}