#pragma once

#include "Core/Core.h"

namespace Render2D::Renderer
{

	class ElementBuffer
	{
	public:
		ElementBuffer(uint32_t* indices, uint32_t count);
		~ElementBuffer();

		void Bind() const;
		void Unbind() const;

		uint32_t GetID() const { return m_ID; }
		uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_ID;
		uint32_t m_Count;
	};

}
