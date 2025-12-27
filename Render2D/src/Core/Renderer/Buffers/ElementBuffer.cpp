#include "ElementBuffer.h"

#include <glad/glad.h>

#include "Core/Logger/Logger.h"

namespace Render2D::Renderer
{

	ElementBuffer::ElementBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

		LOG_TRACE("ElementBuffer created: ID={}, Count={}, Size={} bytes",
			m_ID, count, count * sizeof(uint32_t));
	}

	ElementBuffer::~ElementBuffer()
	{
		glDeleteBuffers(1, &m_ID);
		LOG_TRACE("ElementBuffer destroyed: ID={}", m_ID);
	}

	void ElementBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void ElementBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
