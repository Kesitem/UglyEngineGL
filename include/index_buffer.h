#pragma once

#include "core.h"

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
		IndexBuffer(uint32_t _count, uint32_t* _data);

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

		/**
		 * @brief Get number of indices.
		 *
		 * @return Number of indices
		 */
		uint32_t getCount() const;

	private:

		/*! Index buffer id */
		uint32_t m_id;

		/*! Number of indices */
		uint32_t m_count;
	};
}