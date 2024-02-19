# Minimum CMake version required, we'll just use the latest version.
cmake_minimum_required(VERSION 3.22)

# Project name, version, and description
project(proc VERSION 1.0 DESCRIPTION "idk something low-level")
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Add the directory containing custom CMake modules to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Create an executable
add_executable(${PROJECT_NAME}
    src/main.cpp
)


# target_link_libraries()

# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
