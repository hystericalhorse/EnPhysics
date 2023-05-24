#include "GravitationalEmitter.h"
#include "Object\Body.h"

void GravitationalEmitter::Apply(std::vector<Body*> bodies)
{
	if (bodies.empty()) return;

	for (size_t i = 0; i < bodies.size() - 1; i++)
	{
		for (size_t ii = i + 1; ii < bodies.size(); ii++)
		{
			auto& b = bodies[i];
			auto& B = bodies[ii];

			auto dir = b->position - B->position;

			auto distance = glm::length(dir);
			if (distance == 0) continue;

			distance = glm::max(1.0f, distance);

			auto force = m_strength * ((b->mass * B->mass) / distance);

			auto nrm = glm::normalize(dir);

			b->ApplyImpulse(-nrm * force);
			B->ApplyImpulse( nrm * force);
		}
	}

	
}