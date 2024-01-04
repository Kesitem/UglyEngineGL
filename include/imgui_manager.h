#pragma once

#include "core.h"

namespace ugly
{
	class ImguiManager
	{
	public:

		/**
		 * @brief Constructor.
		 * 
		 * @param _window GlFW window
		 */
		ImguiManager(GLFWwindow* _window);

		/**
		 * @brief Destructor.
		 */
		virtual ~ImguiManager();

		/**
		 * @brief Begin frame.
		 */
		void beginFrame();

		/**
		 * @brief End frame.
		 */
		void endFrame();

		/**
		 * @brief Draw the GUI.
		 */
		void draw();
	};
}