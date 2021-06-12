cmake_minimum_required(VERSION 3.12)

project(UglyEngine VERSION 0.0.2
                  DESCRIPTION "A simple game engine"
                  LANGUAGES CXX)

# Add plog 
find_path(PLOG_INCLUDE_DIRS "plog/Appenders/AndroidAppender.h")

# Add glad
find_package(glad CONFIG REQUIRED)

# Add glfw3
find_package(glfw3 CONFIG REQUIRED)

# Add glm
find_package(glm CONFIG REQUIRED)

# Set sources files path
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Configure version 
configure_file (
    "${INC_DIR}/config.h.in"
    "${INC_DIR}/config.h"
)

# List of header files
set(HEADERS
    UglyEngine.h
    config.h
    Core.h
    Engine.h
    Application.h
    InputStats.h
    InputButton.h
    InputManager.h
    GL.h
    VertexArrays.h
    BufferObject.h
    Program.h
    Shader.h
)
# List of source files
set(SRCS
    LogFormatter.h
    LogFormatter.cpp
    Engine.cpp
    Application.cpp
    InputButton.cpp
    InputManager.cpp
    GL.cpp
    VertexArrays.cpp
    BufferObject.cpp
    Program.cpp
    Shader.cpp
)

# Generate filename with path
foreach(H ${HEADERS})
    list(APPEND ALL_HEADERS ${INC_DIR}/${H})
endforeach() 
foreach(S ${SRCS})
    list(APPEND ALL_SRCS ${SRC_DIR}/${S})
endforeach()

# Create library
add_library(${PROJECT_NAME} STATIC ${ALL_SRCS} ${ALL_HEADERS})

# Set C++17 feature
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Add directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PLOG_INCLUDE_DIRS})

# Add library
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad glfw glm::glm)

# Set include directory for compilation
target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/include)

# Set include directory for clients
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${INC_DIR}/${PROJECT_NAME}>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    PRIVATE src)

# Add tests
add_subdirectory(tests)