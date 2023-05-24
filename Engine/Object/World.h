#pragma once
#include "Object\Body.h"
#include "Emitters\ForceEmitter.h"
#include "Joints\Joint.h"
#include <list>
#include <vector>

class World
{
public:
	~World();

	void Step(float deltaTime, float timeScale = 1.0f);
	void Draw(class Graphics* graphics);

	void AddBody(Body* object);
	void RemoveBody(Body* object);

	void AddEmitter(ForceEmitter* emitter);
	void RemoveEmitter(ForceEmitter* emitter);

	void AddJoint(Joint* joint);
	void RemoveJoint(Joint* joint);

	std::list<Body*> GetBodies() { return m_bodies; }
	std::list<ForceEmitter*> GetEmitters() { return m_emitters; }
	std::list<Joint*> GetJoints() { return m_joints; }

	static glm::vec2 gravity;

private:
	std::list<Body*> m_bodies;
	std::list<ForceEmitter*> m_emitters;
	std::list<Joint*> m_joints;
};