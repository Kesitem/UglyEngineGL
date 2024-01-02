#pragma once

#include "core.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

namespace ugly
{
    class VertexArrays
    {
    public:

        /**
         * @brief Constructor.
         */
        VertexArrays();

        /**
         * @brief Destructor. 
         */
        virtual ~VertexArrays();

        /**
         * @brief Add a vertex buffer.
         * 
         * @param _vertex_buffer Vertex buffer
         */
        void addVertexBuffer(const std::shared_ptr<VertexBuffer>& _vertex_buffer);

        /**
         * @brief Set index buffer.
         *
         * @param index_buffer Index buffer
         */
        void setIndexBuffer(const std::shared_ptr<IndexBuffer>& _index_buffer);

        /**
         * @brief Get index buffer.
         * 
         * @return Index buffer
         */
        std::shared_ptr<IndexBuffer> getIndexBuffer() const;

        /**
         * @brief Bind the vertex arrays.
         */
        void bind();

        /**
         * @brief Unbind the vertex arrays.
         */
        void unbind();

    private:

        /*! Vertex arrays id */
        uint32_t m_id{0};

        /*! Number of vertex attrib */
        uint32_t m_vertex_attrib_index{ 0 };

        /*! Vertex buffers */
        std::vector < std::shared_ptr<VertexBuffer> > m_vertex_buffers;

        /*! Index buffer */
        std::shared_ptr<IndexBuffer> m_index_buffer;
    };

}//namespace ugly