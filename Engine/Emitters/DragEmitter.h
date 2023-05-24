#pragma once
#include "ForceEmitter.h"

class DragEmitter : public ForceEmitter
{
public:
	DragEmitter(class Body* body, float magnitude = 0) :
		ForceEmitter{ body }, m_magnitude{ magnitude }
	{}

	virtual void Apply(std::vector<class Body*> bodies);

protected:
	float m_magnitude{ 0.0f };
};
