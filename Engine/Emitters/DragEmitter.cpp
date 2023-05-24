#include "DragEmitter.h"
#include "Object\Body.h"

#include <gtx/quaternion.hpp>

void DragEmitter::Apply(std::vector<class Body*> bodies)
{
	for (auto& body : bodies)
	{
		if (!m_body->Intersects(body)) continue;

		auto f = 0.5f * (glm::length(body->velocity) * glm::length(body->velocity)) * m_magnitude;
		glm::vec2 force = glm::normalize(body->velocity);

		body->ApplyImpulse(force * -f);
	}
}