#pragma once
#include "glm.hpp"

class Shape
{
public:
	Shape() {}
	Shape(const glm::vec4& color) : color{ color } {}

	virtual void Draw(class Graphics* graphics, const glm::vec2& position) = 0;

	float scale{ 1.0f };
	glm::vec4 color{ 1.0f };
};