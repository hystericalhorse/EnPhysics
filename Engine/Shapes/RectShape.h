#pragma once
#include "Shape.h"

class RectShape : public Shape
{
public:
	RectShape(float width, float height, const glm::vec4& color, bool filled = true) :
		width{ width }, height{ height }, Shape(color), isFilled{ filled }
	{}

	void Draw(class Graphics* graphics, const glm::vec2& position) override;

	float width{ 1.0f };
	float height{ 1.0f };

	glm::vec2 offset{ 0.0f };

	bool isFilled{ true };
};