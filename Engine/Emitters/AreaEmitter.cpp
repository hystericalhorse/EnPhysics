#include "AreaEmitter.h"
#include "Object\Body.h"

#include <gtx/quaternion.hpp>

void AreaEmitter::Apply(std::vector<class Body*> bodies)
{
	for (auto& body : bodies)
	{
		if (!m_body->Intersects(body)) continue;

		glm::quat quat = glm::angleAxis(glm::radians(m_angle), glm::vec3{ 0, 0, 1 });
		glm::vec2 force = quat * glm::vec3{ 1, 0, 0 };

		body->ApplyImpulse(force * m_magnitude);
	}
}