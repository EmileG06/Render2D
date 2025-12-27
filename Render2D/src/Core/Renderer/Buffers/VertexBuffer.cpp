#include "VertexBuffer.h"

#include <glad/glad.h>

#include "Core/Logger/Logger.h"

namespace Render2D::Renderer
{

	VertexBuffer::VertexBuffer(uint32_t size)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

		LOG_TRACE("VertexBuffer created (dynamic): ID={}, Size={} bytes", m_ID, size);
	}

	VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

		LOG_TRACE("VertexBuffer created (static): ID={}, Size={} bytes", m_ID, size);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
		LOG_TRACE("VertexBuffer destroyed: ID={}", m_ID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::SetData(float* vertices, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
		LOG_TRACE("VertexBuffer data updated: ID={}, Size={} bytes", m_ID, size);
	}

}
