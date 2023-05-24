#pragma once

#include "ForceEmitter.h"

class AreaEmitter : public ForceEmitter
{
public:
	AreaEmitter(class Body* body, float magnitude = 1, float angle = 0) :
		ForceEmitter{ body }, m_magnitude{ magnitude }, m_angle{ angle }
	{}

	virtual void Apply(std::vector<class Body*> bodies);

protected:
	float m_magnitude{ 1.0f };
	float m_angle{ 0.0f };
};