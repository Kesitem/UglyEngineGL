#pragma once

#include "Core.h"

namespace ugly
{

	class DisplayManager
	{
	public:

		enum class PolygoneMode : uint32_t
		{
			POINT = 6912,
			LINE = 6913,
			FILL = 6914
		};

		/**
		 * @brief Constructor.
		 */
		DisplayManager();

		/**
		 * @brief Destructor.
		 */
		virtual ~DisplayManager();


		/**
		 * @brief Set the viewport.
		 * 
		 * @param _x     left corner
		 * @param _y     lower corner
		 * @param _width     width
		 * @param _height    height
		 */
		void setViewport(int _x, int _y, unsigned int _width, unsigned _height);

		/**
		 * @brief Specify clear values for the color buffers.
		 *
		 * @param _red      red value
		 * @param _green    green value
		 * @param _blue     blue value
		 * @param _alpha    alpha value
		 */
		void setClearColor(float _red, float _green, float _blue, float _alpha);

		/**
		 * @brief Clear buffers to preset values.
		 */
		void clear();

		/**
		 * @brief Select a polygon rasterization mode.
		 *
		 * @param _mode Specifies how polygons will be rasterized
		 */
		void setPolygonMode(PolygoneMode _mode);

		/**
         * @brief Render primitives from array data.
         * 
		 * @param _count    Number of indices to render
         * @param _first    Starting index
         */
		void drawArrays(uint32_t _count, int32_t _first = 0);

		/**
		 * @brief Render primitives from array data with index buffer.
		 *
		 * @param _count    Number of elements to be rendered. If 0 the full index buffer is used
		 */
		void drawElements(uint32_t _count = 0);
	};

}