#pragma once

#include "Core.h"
#include "Task.h"

namespace ugly
{
	class TaskManager
	{
	public:

		/**
		 * @brief Constructor.
		 */
		TaskManager();

		/**
		 * @brief Destructor.
		 */
		virtual ~TaskManager();

		/**
		 * @brief Push a new task.
		 * 
		 * @param _task Push a new task
		 */
		void pushTask(std::shared_ptr<Task> _task);

		/**
		 * @brief Pop a task.
		 *
		 * @param _task	Task to pop 
		 */
		void popTask(std::shared_ptr<Task> _task);

		/**
		 * @brief Update all tasks.
		 */
		void update();

		/**
		 * @brief Update GUI for all tasks.
		 */
		void updateGui();

		/**
		 * @brief Make the task rendering.
		 */
		void render();

	private:

		std::list< std::shared_ptr<Task> > m_update_list;

		std::list < std::shared_ptr<Task> > m_update_gui_list;

		std::list < std::shared_ptr<Task> > m_render_list;
	};
}