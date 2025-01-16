#pragma once

// C++ standards libs
#include <array>
#include <memory>
#include <map>
#include <string>
#include <fstream>
#include <filesystem>

// plog
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Log.h>

// glad
#include <glad/glad.h>

// opengl
#include <GLFW/glfw3.h>

// Include glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// Include imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// Include stb
#include "stb_image.h"

namespace ugly
{
	static const std::string LOG_FILENAME = "UglyEngine.log";
}