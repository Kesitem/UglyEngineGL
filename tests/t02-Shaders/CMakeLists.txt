cmake_minimum_required(VERSION 3.12)

project(t02-Shaders VERSION 1.0.0
                    DESCRIPTION "Use shaders"
                    LANGUAGES CXX)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Configure version 
configure_file (
    "${SRC_DIR}/config.h.in"
    "${SRC_DIR}/config.h"
)

# List of source files
set(SRCS
    config.h
    SimpleTriangleTask.h
    SimpleTriangleTask.cpp
    UniformTask.h
    UniformTask.cpp
    MoreAttributesTask.h
    MoreAttributesTask.cpp
    UpsideDownTask.h
    UpsideDownTask.cpp
    OffsetTask.h
    OffsetTask.cpp
    PosAsColorTask.h
    PosAsColorTask.cpp
    TestApplication.h
    TestApplication.cpp
    main.cpp
)
# Generate filename with path
foreach(S ${SRCS})
    list(APPEND ALL_SRCS ${SRC_DIR}/${S})
endforeach()

add_executable(${PROJECT_NAME} ${ALL_SRCS})

# Set C++17 feature
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE UglyEngine)

# Copy data directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data)