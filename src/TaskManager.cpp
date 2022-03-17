#include "TaskManager.h"

ugly::TaskManager::TaskManager()
{
}


ugly::TaskManager::~TaskManager()
{
}


void ugly::TaskManager::pushTask(std::shared_ptr<ugly::Task> _task)
{
	m_update_list.push_back(_task);
	m_update_list.sort([](std::shared_ptr<ugly::Task> _lt, std::shared_ptr<ugly::Task> _rt) {
		return _lt->getUpdateOrder() < _rt->getUpdateOrder();
	});

	m_update_gui_list.push_back(_task);
	m_update_gui_list.sort([](std::shared_ptr<ugly::Task> _lt, std::shared_ptr<ugly::Task> _rt) {
		return _lt->getUpdateGuiOrder() < _rt->getUpdateGuiOrder();
		});

	m_render_list.push_back(_task);
	m_render_list.sort([](std::shared_ptr<ugly::Task> _lt, std::shared_ptr<ugly::Task> _rt) {
		return _lt->getRenderOrder() < _rt->getRenderOrder();
		});

}


void ugly::TaskManager::popTask(std::shared_ptr<ugly::Task> _task)
{
	m_update_list.remove(_task);
	m_update_gui_list.remove(_task);
	m_render_list.remove(_task);
}


void ugly::TaskManager::update()
{
	for (const auto& task : m_update_list)
		task->update();
}


void ugly::TaskManager::updateGui()
{
	for (const auto& task : m_update_gui_list)
		task->updateGui();
}


void ugly::TaskManager::render()
{
	for (const auto& task : m_render_list)
		task->render();
}



