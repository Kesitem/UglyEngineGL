cmake_minimum_required(VERSION 3.12)

project(t00-SimpleWindow VERSION 1.0.0
                                DESCRIPTION "Create a simple window"
                                LANGUAGES CXX)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

configure_file (
    "${SRC_DIR}/config.h.in"
     "${SRC_DIR}/config.h"
)

add_executable(${PROJECT_NAME} ./src/main.cpp ./src/config.h)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME} PRIVATE UglyEngineGL)
