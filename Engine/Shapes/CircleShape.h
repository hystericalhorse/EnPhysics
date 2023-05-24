#pragma once
#include "Shape.h"

class CircleShape : public Shape
{
public:
	CircleShape(float radius, const glm::vec4& color, bool filled = true) :
		radius{ radius }, Shape(color), isFilled{ filled }
	{}
	
	void Draw(class Graphics* graphics, const glm::vec2& position) override;

	float radius{ 1.0f };
	bool isFilled{ true };
};