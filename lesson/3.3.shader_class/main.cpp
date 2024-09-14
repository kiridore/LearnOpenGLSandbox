#include "common/app.hpp"
#include "common/shader.hpp"
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

class ExampleShader : public Entry::AppI {
public:
    ExampleShader(std::string name, std::string desc)
        : Entry::AppI(name, desc),
          shader("./asset/shader/3.3.shader_class_vert.glsl",
                 "./asset/shader/3.3.shader_class_frag.glsl") {}

    void Init() override {
        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(GetMainWindow(),
                                       framebuffer_size_callback);

        // VAO
        glGenVertexArrays(1, &VAO_);
        glBindVertexArray(VAO_);
        // create VBO
        glGenBuffers(1, &VBO_);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                              (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                              (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }

    bool Update() override {
        if (this->GetMainWindow() == nullptr) return false;
        if (glfwWindowShouldClose(GetMainWindow())) return false;

        processInput(GetMainWindow());
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        glBindVertexArray(VAO_);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        return true;
    }

    int Shutdown() override {
        glfwTerminate();
        return 0;
    }

private:
    GLuint VBO_, VAO_;

    Shader shader;
};

ENTRY_IMPLEMENT_MAIN(ExampleShader, "ExampleHelloTriangle",
                     "https://learnopengl.com/Getting-started/Shaders")
