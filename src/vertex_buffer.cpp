#include "vertex_buffer.h"


ugly::BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
    : m_elements(elements)
{
    calculateOffsetsAndStride();
}


void ugly::BufferLayout::calculateOffsetsAndStride()
{
    size_t offset = 0;
    m_stride = 0;
    for (auto& element : m_elements)
    {
        element.offset = offset;
        offset += element.size;
        m_stride += element.size;
    }
}


uint32_t ugly::BufferLayout::getStride() const 
{ 
    return m_stride; 
}


const std::vector<ugly::BufferElement>& ugly::BufferLayout::getElements() const 
{ 
    return m_elements; 
}


ugly::VertexBuffer::VertexBuffer(size_t size)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
}


ugly::VertexBuffer::VertexBuffer(size_t _size, const void * _data)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, _size, _data, GL_STATIC_DRAW);
}


ugly::VertexBuffer::~VertexBuffer()
{
    if (m_id != 0)
    {
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }
}


void ugly::VertexBuffer::setData(size_t _size, const void* _data)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, _size, _data);
}


void ugly::VertexBuffer::setLayout(const BufferLayout& layout) 
{ 
    m_layout = layout; 
}


ugly::BufferLayout ugly::VertexBuffer::getLayout() const 
{ 
    return m_layout; 
}


void ugly::VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}


void ugly::VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}