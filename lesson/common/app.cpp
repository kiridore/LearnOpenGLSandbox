#include "app.hpp"

#include <iostream>

namespace Entry {
AppI::AppI(std::string name, std::string description)
    : name_(name), desc_(description) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window_ = glfwCreateWindow(800, 600, name_.c_str(), NULL, NULL);

    if (window_ == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
}


int RunApp(AppI* _app) {
    _app->Init();

    while(_app->Update()) {
        glfwSwapBuffers(_app->GetMainWindow());
        glfwPollEvents();
    }

    return _app->Shutdown();
}

const std::string& AppI::GetName() {
    return name_;
}

const std::string& AppI::GetDescription() {
    return desc_;
}

GLFWwindow * AppI::GetMainWindow() {
    return window_;
}

}  // namespace Entry
