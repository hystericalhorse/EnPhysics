#pragma once
#include "ForceEmitter.h"

class PointEmitter : public ForceEmitter
{
public:
	PointEmitter(class Body* body, float magnitude) :
		ForceEmitter{body}, m_magnitude{magnitude}
	{}

	virtual void Apply(std::vector<class Body*> bodies);

protected:
	float m_magnitude{ 1.0f };
};