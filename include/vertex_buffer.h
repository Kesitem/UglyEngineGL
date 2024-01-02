#pragma once

#include "core.h"

namespace ugly
{
    enum class BufferDataType
    {
        FLOAT2,
        FLOAT3
    };

    static uint32_t getBufferDataTypeSize(BufferDataType _type)
    {
        switch (_type)
        {
        case BufferDataType::FLOAT2:   return 4 * 2;
        case BufferDataType::FLOAT3:   return 4 * 3;
        }

        return 0;
    }

    static uint32_t getBufferDataTypeComponentCount(BufferDataType _type)
    {
        switch (_type)
        {
        case BufferDataType::FLOAT2:   return 2;
        case BufferDataType::FLOAT3:   return 3;
        }

        return 0;
    }
    
    static uint32_t getBufferDataTypeComponentOpenglType(BufferDataType _type)
    {
        switch (_type)
        {
        case BufferDataType::FLOAT2:    return GL_FLOAT;
        case BufferDataType::FLOAT3:    return GL_FLOAT;
        }

        return 0;
    }

    struct BufferElement
    {
        std::string name;
        BufferDataType type;
        uint32_t size;
        size_t offset;
        bool normalized;

        BufferElement() = default;

        BufferElement(std::string _name, BufferDataType _type, bool _normalized) : name(_name), type(_type), size(getBufferDataTypeSize(_type)), offset(0), normalized(_normalized)
        {
        }
    };

    class BufferLayout
    {
    public:

        /**
         * @brief Default constructor.
         */
        BufferLayout() {}
        
        /**
         * @brief Constructor with initializer list.
         * 
         * @param   _elements    Initializer list of elements
         */
        BufferLayout(std::initializer_list<BufferElement> _elements);

        /**
         * @brief Get buffer stride.
         *
         * @return Layout stride
         */
        uint32_t getStride() const;

        /**
         * @brief Get elements.
         *
         * @return Elements
         */
        const std::vector<BufferElement>& getElements() const;

    private:

        void calculateOffsetsAndStride();

    private:

        /*! Elements */
        std::vector<BufferElement> m_elements;

        /*! Stride */
        uint32_t m_stride = 0;
    };


    /**
     * @brief Vertex buffer. 
     */
    class VertexBuffer
    {
    public:

        /**
         * @brief Constructor.
         * 
         * * @param _size     Size in bytes
         */
        VertexBuffer(size_t _size);

        /**
         * @brief Constructor with initialization.
         * 
         * @param _size     Size in bytes
         * @param _data     Data or nullptr
         */
        VertexBuffer(size_t _size, const void* _data);

        /**
         * @brief Destructor.
         */
        virtual ~VertexBuffer();

        /**
         * @brief Set Data of the buffer.
         *  
         * @param _size     Size in bytes
         * @param _data     Data or nullptr
         */
        void setData(size_t _size, const void * _data);

        /**
         * @brief Set buffer layout.
         *
         * @param  _layout Buffer layout
         */
        void setLayout(const BufferLayout& _layout);

        /**
         * @brief Get buffer layout.
         *
         * @return Buffer layout
         */
        BufferLayout getLayout() const;
        
        /**
         * @brief Bind the vertex buffer.
         */
        void bind();

        /**
         * @brief Unbind the vertex buffer.
         */
        void unbind();

    private:

        /** Object id */
        uint32_t m_id;

        /** Layout */
        BufferLayout m_layout;
    };
}