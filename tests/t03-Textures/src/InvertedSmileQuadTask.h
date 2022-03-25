#include "UglyEngine.h"

class InvertedSmileQuadTask : public ugly::Task
{
public:

	/**
	 * @brief Constructor.
	 */
	InvertedSmileQuadTask();

	/**
	 * @brief Destructor.
	 */
	virtual ~InvertedSmileQuadTask();

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

	std::shared_ptr<ugly::Texture> m_texture0{ nullptr };

	std::shared_ptr<ugly::Texture> m_texture1{ nullptr };
};