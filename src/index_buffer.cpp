#include "index_buffer.h"

ugly::IndexBuffer::IndexBuffer(uint32_t _count, uint32_t* _indices) : m_count(_count)
{
	glCreateBuffers(1, &m_id);

	// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
	// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, _count * sizeof(uint32_t), _indices, GL_STATIC_DRAW);
}


ugly::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_id);
}


void ugly::IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}


void ugly::IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t ugly::IndexBuffer::getCount() const
{
	return m_count;
}
