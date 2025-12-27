#pragma once

#include "Core/Core.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"

namespace Render2D::Renderer
{

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void AddElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer);

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const std::shared_ptr<ElementBuffer>& GetElementBuffer() const { return m_ElementBuffer; }

		uint32_t GetID() const { return m_ID; }

	private:
		uint32_t m_ID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<ElementBuffer> m_ElementBuffer;
	};

}
