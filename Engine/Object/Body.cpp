#include "Object\Body.h"
#include "Math\Integrator.h"
#include "Shapes\CircleShape.h"
#include "World.h"

void Body::Step(float deltaTime)
{
	if (lifetime > 0) lifetime -= deltaTime;

	if (type != Type::Dynamic) return;

	if (hasGravity) AddForce(World::gravity * gravityScale * mass);

	Integrator::SemiImplicitEuler(*this, deltaTime);
	clearImpulse();

	velocity *= 1.0f / (1.0f + (deltaTime * damping));
}

void Body::Draw(Graphics* graphics)
{
	shape->Draw(graphics, this->position);
}

void Body::AddForce(const glm::vec2& force)
{
	this->force += force;
}
void Body::ApplyImpulse(const glm::vec2& impulse)
{
	this->impulse += impulse;
}

bool Body::Intersects(Body* other)
{
	glm::vec2 dir = other->position - this->position;
	float distance = glm::length(dir);
	float crad = ((CircleShape*)this->shape)->radius + ((CircleShape*)other->shape)->radius;

	return distance <= crad;
}