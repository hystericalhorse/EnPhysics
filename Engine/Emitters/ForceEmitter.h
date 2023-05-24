#pragma once
#include <vector>

class ForceEmitter
{
public:
	ForceEmitter() {}
	ForceEmitter(class Body* body) : m_body{body} {}

	virtual void Apply(std::vector<class Body*> bodies) = 0;
	virtual void Draw(class Graphics* graphics);

protected:
	class Body* m_body{ nullptr };
	// if physicsobject draw it in Draw function.
};