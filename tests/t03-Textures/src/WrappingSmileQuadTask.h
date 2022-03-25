#include "UglyEngine.h"

class WrappingSmileQuadTask : public ugly::Task
{
public:

	/**
	 * @brief Constructor.
	 */
	WrappingSmileQuadTask();

	/**
	 * @brief Destructor.
	 */
	virtual ~WrappingSmileQuadTask();

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

	int m_wrapping_method{ 0 };

	std::shared_ptr<ugly::VertexArrays> m_va{ nullptr };

	std::shared_ptr<ugly::Program> m_program{ nullptr };

	std::shared_ptr<ugly::Texture> m_texture0{ nullptr };

	std::shared_ptr<ugly::Texture> m_texture1{ nullptr };
};