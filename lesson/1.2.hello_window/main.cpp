#include "common/app.hpp"
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

class ExampleHelloWindow : public Entry::AppI {
public:
    ExampleHelloWindow(std::string name, std::string desc)
        : Entry::AppI(name, desc) {}

    void Init() override {
        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(GetMainWindow(), framebuffer_size_callback);
    }

    bool Update() override {
        if (this->GetMainWindow() == nullptr) return false;
        if (glfwWindowShouldClose(GetMainWindow())) return false;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        return true;
    }

    int Shutdown() override {
        glfwTerminate();
        return 0;
    }

private:
};

ENTRY_IMPLEMENT_MAIN(ExampleHelloWindow, "ExampleHelloWindow",
                     "https://learnopengl.com/Getting-started/Hello-Window")
