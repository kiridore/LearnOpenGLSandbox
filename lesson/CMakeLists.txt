add_library(common "")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_sources(common
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/common/app.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/app.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/shader.hpp
)

target_link_libraries(common glfw glad)

function (generate_example name)
    file(GLOB src_list ${name}/*.cpp)
    add_executable(${name} ${src_list})
    target_link_libraries(${name} common)
endfunction()

generate_example(1.1.hello_window)
generate_example(2.1.hello_triangle)
generate_example(3.1.shader_uniform)
generate_example(3.2.shader_interpolation)
generate_example(3.3.shader_class)

