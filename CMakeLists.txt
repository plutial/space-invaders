cmake_minimum_required(VERSION 3.15)

# Wayland
SET(GLFW_BUILD_WAYLAND ON)

# Project name
project(space-invaders)

# Requires at least version 3.0
# find_package(raylib 3.0 REQUIRED) 
set(CMAKE_BUILD_TYPE Debug)
add_subdirectory("raylib" EXCLUDE_FROM_ALL)

# Required for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Requires C11 standard
set(CMAKE_C_STANDARD 11)

# Flags 
SET(COMPILE_FLAGS   "-Wall -Wextra -fsanitize=address")
SET(LINK_FLAGS      "-Wall -Wextra -fsanitize=address")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")

# Source files
file(GLOB SOURCE_FILES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link raylib
target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
