#include "PointEmitter.h"
#include "Object\Body.h"

void PointEmitter::Apply(std::vector<class Body*> bodies)
{
	for (auto& body : bodies)
	{
		if (!m_body->Intersects(body)) continue;

		auto dir = m_body->position - body->position;
		auto force = glm::normalize(dir);

		body->ApplyImpulse(force * m_magnitude);
	}
}