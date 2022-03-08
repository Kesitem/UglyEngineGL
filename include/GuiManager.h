#pragma once

#include "Core.h"

namespace ugly
{
	class GuiManager
	{
	public:

		/**
		 * @brief Constructor.
		 * 
		 * @param _window GlFW window
		 */
		GuiManager(GLFWwindow* _window);

		/**
		 * @brief Destructor.
		 */
		virtual ~GuiManager();

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