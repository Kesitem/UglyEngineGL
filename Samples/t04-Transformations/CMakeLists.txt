cmake_minimum_required(VERSION 3.12)

project(t04-Transformations VERSION 1.0.0
                                DESCRIPTION "Transformation samples"
                                LANGUAGES CXX)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

configure_file (
    "${SRC_DIR}/config.h.in"
     "${SRC_DIR}/config.h"
)

add_executable(${PROJECT_NAME} ./src/main.cpp ./src/config.h ./src/test_application.h ./src/test_application.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME} PRIVATE UglyEngineGL)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data)
