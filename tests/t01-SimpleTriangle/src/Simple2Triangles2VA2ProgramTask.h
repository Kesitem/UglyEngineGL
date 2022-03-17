#include "UglyEngine.h"

class Simple2Triangles2VA2ProgramTask : public ugly::Task
{
public:

	/**
	 * @brief Constructor.
	 */
	Simple2Triangles2VA2ProgramTask();

	/**
	 * @brief Destructor.
	 */
	virtual ~Simple2Triangles2VA2ProgramTask();

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

private:

	std::shared_ptr<ugly::VertexArrays> m_va0{ nullptr };

	std::shared_ptr<ugly::VertexArrays> m_va1{ nullptr };

	std::shared_ptr<ugly::Program> m_program0{ nullptr };

	std::shared_ptr<ugly::Program> m_program1{ nullptr };
};