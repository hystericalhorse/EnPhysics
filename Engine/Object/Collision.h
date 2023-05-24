#pragma once
#include "glm.hpp"
#include <vector>

struct Contact
{
	class Body* b{ nullptr };
	class Body* B{ nullptr };

	float restitution{ 0.0f };
	float depth{ 0.0f };
	glm::vec2 normal{ 0.0f, 0.0f };
};

class Collision
{
public:
	Collision() {}
	~Collision() {}



private:


};