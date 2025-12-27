#pragma once

namespace Render2D
{

	class Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnEvent(Event& event) { }

		virtual void OnUpdate(float deltaTime) { }
		virtual void OnRender() { }
	};

}
