#include "UglyEngine.h"

class Simple2TrianglesTask : public ugly::Task
{
public:

	/**
	 * @brief Constructor.
	 */
	Simple2TrianglesTask();

	/**
	 * @brief Destructor.
	 */
	virtual ~Simple2TrianglesTask();

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

	std::shared_ptr<ugly::VertexArrays> m_va{ nullptr };

	std::shared_ptr<ugly::Program> m_program{ nullptr };
};