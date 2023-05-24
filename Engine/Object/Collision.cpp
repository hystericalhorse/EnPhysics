#include "Collision.h"
#include "Math/Random.h"
#include "Shapes/CircleShape.h"
#include "Shapes/RectShape.h"

namespace Collision
{
	Contact GetContact(Body* b, Body* B)
	{
		Contact contact;

		contact.b = b;
		contact.B = B;

		glm::vec2 dir = b->position - B->position;
		float dis = glm::length(dir);
		if (dis == 0.0f)
		{
			dir = { randomf(-0.05f, 0.05f), randomf(-0.05f, 0.05f) };
		}

		double radius = ((CircleShape*)b->shape)->radius + ((CircleShape*)B->shape)->radius;
		contact.depth = radius - dis;

		contact.normal = glm::normalize(dir);

		contact.restitution = randomf(1, 2);

		return contact;
	}

	void CreateContacts(std::vector<Body*> bodies, std::vector<Contact>& contacts)
	{
		if (bodies.empty()) return;

		for (size_t i = 0; i < bodies.size() - 1; i++)
		{
			for (size_t ii = i + 1; ii < bodies.size(); ii++)
			{
				Body* b = bodies[i];
				Body* B = bodies[ii];

				// contact needs at least one dynamic body
				if (b->type != Body::Dynamic && B->type != Body::Dynamic) continue;

				// check for intersection between bodies
				if (b->Intersects(B))
				{
					// create contact
					Contact contact = Collision::GetContact(b, B);
					contacts.push_back(contact);
				}
			}
		}
	}

	void Separate(std::vector<Contact>& contacts)
	{
		for (auto& contact : contacts)
		{
			auto t_imass = contact.b->imass + contact.B->imass;
			//if (t_imass == 0) t_imass = randomf();

			glm::vec2 separation = contact.normal * (contact.depth / t_imass);

			//contact.b->ApplyImpulse( separation * contact.b->imass * contact.depth);// * (float)pow(2, contact.restitution));
			//contact.B->ApplyImpulse(-separation * contact.B->imass * contact.depth);// * (float)pow(2, contact.restitution));

			contact.b->position += (separation * contact.b->imass);
			contact.B->position -= (separation * contact.B->imass);
		}
	}
}

