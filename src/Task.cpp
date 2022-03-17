#include "Task.h"
#include "Engine.h"


ugly::Task::Task()
{
    m_display_manager = ugly::Engine::getInstance()->getDisplayManager();
}


ugly::Task::~Task()
{
}

void ugly::Task::initialize()
{
}

void ugly::Task::shutdown()
{
}


void ugly::Task::update()
{
}


void ugly::Task::updateGui()
{
}


void ugly::Task::render()
{
    LOG_DEBUG << "Base task render";
}


const std::string& ugly::Task::getName() const
{
    return m_name;
}


uint32_t ugly::Task::getUpdateOrder() const
{
    return m_update_order;
}


uint32_t ugly::Task::getUpdateGuiOrder() const
{
    return m_update_gui_order;
}


uint32_t ugly::Task::getRenderOrder() const
{
    return m_render_order;
}


