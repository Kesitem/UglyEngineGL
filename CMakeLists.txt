cmake_minimum_required(VERSION 3.12)

project(UglyEngineGL VERSION 0.0.1
                  DESCRIPTION "A simple OpenGL game engine"
                  LANGUAGES CXX)

# Add plog
find_package(plog CONFIG REQUIRED)

# Add glm
find_package(glm CONFIG REQUIRED)

# Add glfw3
find_package(glfw3 CONFIG REQUIRED)

# Add glad
find_package(glad CONFIG REQUIRED)

# Add imgui
find_package(imgui CONFIG REQUIRED)

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
    core.h
    engine.h
    application.h
    input_state.h
    input_button.h 
    input_manager.h
    display_manager.h
    vertex_buffer.h
    index_buffer.h
    vertex_arrays.h
    shader.h 
    program.h
    imgui_manager.h
)

# List of source files
set(SRCS
    engine.cpp
    log_formatter.cpp
    log_formatter.h
    application.cpp
    input_button.cpp 
    input_manager.cpp
    display_manager.cpp
    vertex_buffer.cpp
    index_buffer.cpp
    vertex_arrays.cpp
    shader.cpp 
    program.cpp
    imgui_manager.cpp
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
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Add directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PLOG_INCLUDE_DIRS} ${Stb_INCLUDE_DIR})

# Add library
target_link_libraries(${PROJECT_NAME} PUBLIC plog::plog glfw glad::glad glm::glm imgui::imgui)

# Set include directory for compilation
target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/include)

# Set include directory for clients
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${INC_DIR}/${PROJECT_NAME}>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    PRIVATE src)

add_subdirectory(Samples)