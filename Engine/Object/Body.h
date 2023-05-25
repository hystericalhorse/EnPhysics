#pragma once
#include "glm.hpp"
#include "Shapes\Shape.h"

class Body
{
public:
	enum Type { Dynamic, Kinematic, Static };

	Body() {}
	
	Body(const glm::vec2& position = { 0, 0 }, Shape* shape = nullptr, const glm::vec2& velocity = { 0, 0 }, float mass = 1.0f, Type type = Type::Dynamic, float damping = 0.0f)
		: mass{ mass }, shape{ shape }, position { position }, velocity{ velocity }, type{ type }, damping{ damping }
	{
		imass = (mass == 0 || type != Dynamic) ? 0 : 1 / mass;
	}

	void Step(float deltaTime);
	void Draw(class Graphics* graphics);

	void AddForce(const glm::vec2& force);
	void ApplyImpulse(const glm::vec2& impulse);

	void resetForce() { force = glm::vec2{ 0.0f }; }
	void clearImpulse() { impulse = glm::vec2{ 0.0f }; }

	bool Intersects(class Body* other);

	//

	Type type = Type::Dynamic;
	Shape* shape{ nullptr };

	float lifetime{ 0.0f };

	float mass{ 1.0f };
	float imass{ 1.0f }; // 1 / mass
	float damping{ 0.0f };
	float restitution{ 0.2f };

	bool hasGravity{ true };
	float gravityScale{ 1.0f };

	glm::vec2 position{ 0.0f };
	glm::vec2 velocity{ 0.0f };

	glm::vec2 force{ 0.0f }; // constant force
	glm::vec2 impulse{ 0.0f }; // momentary force
};