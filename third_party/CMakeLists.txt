# glad
add_subdirectory(glad)

# glfw
add_subdirectory(glfw)

# glm
add_subdirectory(glm)

# imgui
file(GLOB IMGUI_STAR_SOURCE
    "./imgui/imgui*.cpp"
)

set(IMGUI_BACKEND_SOURCE)

list(APPEND IMGUI_BACKEND_SOURCE
    ./imgui/backends/imgui_impl_glfw.cpp
    ./imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC
    ${IMGUI_STAR_SOURCE}
    ${IMGUI_BACKEND_SOURCE}
)

target_include_directories(imgui PUBLIC
    ./imgui/backends/
    ./imgui/
)

target_link_libraries(imgui ${OPENGL_LIBRARIES} glfw)

