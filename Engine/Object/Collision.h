#pragma once
#include <glm.hpp>
#include "Body.h"
#include <vector>

struct Contact
{
	Body* b{ nullptr };
	Body* B{ nullptr };

	float restitution{ 0.0f };
	float depth{ 0.0f };
	glm::vec2 normal{ 0.0f, 0.0f };
};

namespace Collision
{
	void CreateContacts(std::vector<Body*> bodies, std::vector<Contact>& contacts);
	Contact GetContact(Body* b, Body* B);

	void Separate(std::vector<Contact>& contacts);
};