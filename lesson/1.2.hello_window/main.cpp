#include "common/app.hpp"

class ExampleHelloWindow : public Entry::AppI {
public:
    ExampleHelloWindow(std::string name, std::string desc)
        : Entry::AppI(name, desc) {}

    void Init() override { glViewport(0, 0, 800, 600); }

    bool Update() override {
        if (this->GetMainWindow() == nullptr) return false;
        if (glfwWindowShouldClose(GetMainWindow())) return false;

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
