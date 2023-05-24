#pragma once
#include "ForceEmitter.h"

class GravitationalEmitter : public ForceEmitter
{
public:
	GravitationalEmitter() {}
	GravitationalEmitter(float strength) : m_strength{ strength } {}

	virtual void Apply(std::vector<class Body*> bodies) override;

private:
	float m_strength{ 0.0f };

};