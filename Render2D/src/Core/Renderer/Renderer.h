#pragma once

#include "Core/Core.h"

namespace Render2D::Renderer
{
	void ClearScreen(float red, float green, float blue, float alpha);
	void DrawElements(uint32_t count);
}
