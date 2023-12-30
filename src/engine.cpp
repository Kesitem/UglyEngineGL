#include "engine.h"
#include "core.h"
#include "log_formatter.h"

ugly::Engine::Engine()
{
    initializePLog();

    auto path = std::filesystem::current_path();
    LOG_INFO << "Current path: " << path.c_str();
}


ugly::Engine::~Engine()
{
}


void ugly::Engine::initializePLog()
{
    // Remove log file if exists
    struct stat buffer;
    if (stat(LOG_FILENAME.c_str(), &buffer) == 0)
    {
        if (remove(LOG_FILENAME.c_str()) != 0)
        {
            LOG_ERROR << "Cannnot remove log file";
        }
    }

    // Create log
    static plog::RollingFileAppender<plog::LogFormatter> file_appender(LOG_FILENAME.c_str(), 0, 0);
    static plog::ConsoleAppender<plog::LogFormatter> console_appender;

    plog::init(plog::debug, &console_appender).addAppender(&file_appender);
}