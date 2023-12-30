#pragma once

// C++ standards libs
#include <string>
#include <filesystem>

// plog
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Log.h>

namespace ugly
{
	static const std::string LOG_FILENAME = "UglyEngine.log";
}