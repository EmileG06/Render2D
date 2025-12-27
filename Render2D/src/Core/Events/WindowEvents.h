#pragma once

#include "Events.h"

namespace Render2D
{

	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() { }

		EVENT_CLASS_TYPE(WindowClosed);
	};

	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(float width, float height)
			: m_Width(width), m_Height(height) { }

		float GetWidth() const { return m_Width; }
		float GetHeight() const { return m_Height; }

		virtual std::string ToString() const override
		{
			return std::format("WindowResizedEvent: {0}, {1}", GetWidth(), GetHeight());
		}

		EVENT_CLASS_TYPE(WindowResized);

	private:
		float m_Width;
		float m_Height;
	};

}
