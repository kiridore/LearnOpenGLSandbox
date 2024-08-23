#pragma once
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <string>

#define ENTRY_IMPLEMENT_MAIN(_app, ...) \
    int main() {                        \
        _app app(__VA_ARGS__);          \
        return Entry::RunApp(&app);     \
    }

namespace Entry {

class AppI {
public:
    AppI(std::string name, std::string description);

    virtual void Init() = 0;

    virtual int Shutdown() = 0;

    virtual bool Update() = 0;

    const std::string& GetName();

    const std::string& GetDescription();

    GLFWwindow * GetMainWindow();

private:
    std::string name_;
    std::string desc_;

    GLFWwindow *window_ = nullptr;
};

int RunApp(AppI* _app);

}  // namespace Entry
