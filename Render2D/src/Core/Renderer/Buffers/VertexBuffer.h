#pragma once

#include "Core/Core.h"
#include "BufferLayout.h"

namespace Render2D::Renderer
{

	class VertexBuffer
	{
	public:
		VertexBuffer(uint32_t size);
		VertexBuffer(float* vertices, uint32_t size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetData(float* vertices, uint32_t size);

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

		uint32_t GetID() const { return m_ID; }

	private:
		uint32_t m_ID;
		BufferLayout m_Layout;
	};

}
