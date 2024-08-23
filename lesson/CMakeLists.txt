add_library(common "")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_sources(common
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/common/app.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/app.hpp
)

target_link_libraries(common glfw glad)

add_executable(hello_window ${CMAKE_CURRENT_SOURCE_DIR}/1.2.hello_window/main.cpp)

target_link_libraries(hello_window common)
