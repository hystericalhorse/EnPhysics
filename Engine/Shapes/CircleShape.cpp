#include "CircleShape.h"
#include "Engine\Graphics.h"

void CircleShape::Draw(class Graphics* graphics, const glm::vec2& position)
{
	auto r = graphics->WorldToPixels(radius);

	if (isFilled)
		graphics->DrawFilledCircle(graphics->WorldToScreen(position), r, color);
	else
		graphics->DrawCircle(graphics->WorldToScreen(position), r, color);
}