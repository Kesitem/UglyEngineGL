#pragma once

//STL
#include <string>
#include <map>
#include <set>
#include <optional>
#include <fstream>
#include <filesystem>

// Include configuration header
#include "config.h"

// Include plog
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

// Include glad
#include <glad/glad.h> 

// Include GLFW
#include <GLFW/glfw3.h>

// Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// Include stb
#include "stb_image.h"

// Include imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// Constants declaration
namespace ugly
{
	static const std::string ENGINE_NAME = "UglyEngine";
	static const std::string LOG_FILENAME = "UglyEngine.log";

}//namespace ugly