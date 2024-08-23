cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(LearnOpenGLSandbox
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

find_package(OpenGL REQUIRED)

# include
include_directories(${CMAKE_SOURCE_DIR}/third_party/)
include_directories(${CMAKE_SOURCE_DIR}/third_party/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/glm/)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lesson)
