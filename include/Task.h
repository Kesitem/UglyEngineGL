#pragma once

#include "Core.h"
#include "DisplayManager.h"

namespace ugly
{
	class Task
	{
	public:

		/**
		 * @brief Constructor.
		 */
		Task();

		/**
		 * @brief Destructor.
		 */
		virtual ~Task();

		/**
		 * @brief Initialiaze task.
		 */
		virtual void initialize();

		/**
		 * @brief Shutdown task.
		 */
		virtual void shutdown();

		/**
		 * @brief Update task.
		 */
		virtual void update();

		/**
		 * @brief Update imgui.
		 */
		virtual void updateGui();

		/**
		 * @brief Draw task.
		 */
		virtual void render();

		/**
		 * @brief Get task name.
		 *
		 * @return Task name
		 */
		const std::string& getName() const;

		/**
		 * @brief Get update order.
		 *
		 * @return Update order.
		 */
		uint32_t getUpdateOrder() const;

		/**
		 * @brief Get update gui order.
		 *
		 * @return Update gui order.
		 */
		uint32_t getUpdateGuiOrder() const;

		/**
		 * @brief Get render order.
		 *
		 * @return Render order.
		 */
		uint32_t getRenderOrder() const;

	protected:

		/*! Display manager */
		std::shared_ptr<DisplayManager> m_display_manager;

		/*! Task name */
		std::string m_name;

		/*: Is state pause? */
		bool m_pause{ false };

		uint32_t m_update_order {0};

		uint32_t m_update_gui_order {0};

		uint32_t m_render_order {0};
	};
}