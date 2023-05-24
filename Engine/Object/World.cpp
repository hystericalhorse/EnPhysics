#include "World.h"
#include <vector>

glm::vec2 World::gravity{ 0.0f, -9.81f };

World::~World()
{
	for (auto& body: m_bodies) delete body;
	for (auto& emitter : m_emitters) delete emitter;
	for (auto& joint : m_joints) delete joint;

	m_bodies.clear();
	m_emitters.clear();
	m_joints.clear();
}

void World::Step(float deltaTime, float timeScale)
{
	for (auto& joint : m_joints) joint->Step(deltaTime * timeScale);
	for (auto& emitter : m_emitters) emitter->Apply(std::vector<Body*>{std::begin(m_bodies), std::end(m_bodies)});
	for (auto& body : m_bodies) body->Step(deltaTime * timeScale);
}
void World::Draw(class Graphics* graphics)
{
	for (auto& joint : m_joints) joint->Draw(graphics);
	for (auto& emitter : m_emitters) emitter->Draw(graphics);
	for (auto& body : m_bodies) body->Draw(graphics);
}

void World::AddBody(Body* object)
{
	m_bodies.push_back(object);
}
void World::RemoveBody(Body* object)
{
	m_bodies.remove(object);
}

void World::AddEmitter(ForceEmitter* emitter)
{
	m_emitters.push_back(emitter);
}
void World::RemoveEmitter(ForceEmitter* emitter)
{
	m_emitters.remove(emitter);
}

void World::AddJoint(Joint* joint)
{
	m_joints.push_back(joint);
}
void World::RemoveJoint(Joint* joint)
{
	m_joints.remove(joint);
}