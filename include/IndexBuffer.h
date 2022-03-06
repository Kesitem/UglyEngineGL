#pragma once

#include "Core.h"

namespace ugly
{
	/**
	 * \brief Index buffer.
	 */
	class IndexBuffer
	{
	public:

		/**
		 * @brief Constructeur.
		 * 
		 * @param _count	Number of indices
		 * @param _data		Indices
		 */
		IndexBuffer(uint64_t _count, uint32_t* _data);

		/**
		 * @brief Destructor.
		 */
		virtual ~IndexBuffer();

		/**
		 * @brief Bind the buffer.
		 */
		void bind();

		/**
		 * @brief Unbind the buffer.
		 */
		void unbind();

	private:

		/*! Index buffer id */
		uint32_t m_id;

		/*! Number of indices */
		uint64_t m_count;
	};
}