#include "RectShape.h"
#include "Engine\Graphics.h"

void RectShape::Draw(class Graphics* graphics, const glm::vec2& position)
{
	auto offpos = graphics->WorldToScreen(position) + (glm::ivec2)offset;
	auto w = graphics->WorldToPixels(width);
	auto h = graphics->WorldToPixels(height);

	if (isFilled)
	{
		for (size_t i = 0; i < w; i++)
			graphics->DrawLine(offpos + glm::ivec2{i, 0}, offpos + glm::ivec2{ i, h }, color);
	}
	else
	{
		graphics->DrawLine(offpos, offpos + glm::ivec2{w, 0}, color);
		graphics->DrawLine(offpos, offpos + glm::ivec2{0, h}, color);
		graphics->DrawLine(offpos + glm::ivec2{ w, h }, offpos + glm::ivec2{ 0, h }, color);
		graphics->DrawLine(offpos + glm::ivec2{ w, h }, offpos + glm::ivec2{ w, 0 }, color);
	}
}