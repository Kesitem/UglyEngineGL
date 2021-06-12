cmake_minimum_required(VERSION 3.12)

project(t01-SimpleTriangle VERSION 1.0.0
                                DESCRIPTION "Draw a simple triangle"
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