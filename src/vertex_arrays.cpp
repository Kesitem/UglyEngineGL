#include "vertex_arrays.h"


ugly::VertexArrays::VertexArrays()
{
    glGenVertexArrays(1, &m_id);
    bind();
}


ugly::VertexArrays::~VertexArrays()
{
    if (m_id != 0)
    {
        glDeleteVertexArrays(1, &m_id);
        m_id = 0;
    }
}


void ugly::VertexArrays::addVertexBuffer(const std::shared_ptr<VertexBuffer>& _vertex_buffer)
{
    bind();
    _vertex_buffer->bind();

    const auto& layout = _vertex_buffer->getLayout();
    for (const auto& element : layout.getElements())
    {
        switch (element.type)
        {
        case BufferDataType::FLOAT2:
        case BufferDataType::FLOAT3:
            glEnableVertexAttribArray(m_vertex_attrib_index);
            glVertexAttribPointer(m_vertex_attrib_index,
                ugly::getBufferDataTypeComponentCount(element.type),
                ugly::getBufferDataTypeComponentOpenglType(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                layout.getStride(),
                (const void*)element.offset);
            m_vertex_attrib_index++;
            break;
        }
    }

    m_vertex_buffers.push_back(_vertex_buffer);
}


void ugly::VertexArrays::setIndexBuffer(const std::shared_ptr<IndexBuffer>& _index_buffer)
{

    bind();
    _index_buffer->bind();

    m_index_buffer = _index_buffer;
}


std::shared_ptr<ugly::IndexBuffer> ugly::VertexArrays::getIndexBuffer() const
{
    return m_index_buffer;
}


void ugly::VertexArrays::bind()
{
    glBindVertexArray(m_id);
}


void ugly::VertexArrays::unbind()
{
    glBindVertexArray(0);
}