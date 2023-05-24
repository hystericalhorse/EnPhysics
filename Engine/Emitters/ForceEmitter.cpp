#include "ForceEmitter.h"
#include "Object\Body.h"
#include "Engine\Graphics.h"

void ForceEmitter::Draw(Graphics* graphics)
{
	if (m_body) m_body->Draw(graphics);
}