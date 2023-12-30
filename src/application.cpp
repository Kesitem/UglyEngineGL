#include "application.h"
#include "core.h"

ugly::Application::Application()
{
}


ugly::Application::~Application()
{
}


void ugly::Application::initialize()
{
    PLOG_INFO << "Initialize base application";
}


void ugly::Application::shutdown()
{
    PLOG_INFO << "Shutdown base application";
}


void ugly::Application::update()
{
}