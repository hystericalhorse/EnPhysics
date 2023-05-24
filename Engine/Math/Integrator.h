#pragma once
#include "Object\Body.h"

namespace Integrator
{
	void ExplicitEuler(Body& body, float deltaTime)
	{
		body.position += body.velocity * deltaTime;
		body.velocity += (body.impulse * body.imass) * deltaTime;
		body.velocity += (body.force * body.imass) * deltaTime;
	}

	void SemiImplicitEuler(Body& body, float deltaTime)
	{
		body.velocity += (body.impulse * body.imass) * deltaTime;
		body.velocity += (body.force * body.imass) * deltaTime;
		body.position += body.velocity * deltaTime;
	}
}