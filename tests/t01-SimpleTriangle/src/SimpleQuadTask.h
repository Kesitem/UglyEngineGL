#include "UglyEngine.h"

class SimpleQuadTask : public ugly::Task
{
public:

	/**
	 * @brief Constructor.
	 */
	SimpleQuadTask();

	/**
	 * @brief Destructor.
	 */
	virtual ~SimpleQuadTask();

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