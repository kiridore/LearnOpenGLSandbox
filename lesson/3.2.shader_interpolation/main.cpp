#include "common/app.hpp"
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
        : Entry::AppI(name, desc) {}

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
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                              (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // shader
        const char* vert_shader_source = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aColor;

            out vec3 ourColor;

            void main() {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
                ourColor = aColor;
            }
        )";
        GLuint vert_shader;
        vert_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vert_shader, 1, &vert_shader_source, NULL);
        glCompileShader(vert_shader);

        const char* frag_shader_source = R"(
            #version 330 core
            in  vec3 ourColor;
            out vec4 FragColor;

            void main() {
                FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0f);
            }
        )";
        GLuint frag_shader;
        frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag_shader, 1, &frag_shader_source, NULL);
        glCompileShader(frag_shader);

        this->program_ = glCreateProgram();
        glAttachShader(this->program_, vert_shader);
        glAttachShader(this->program_, frag_shader);
        glLinkProgram(this->program_);

        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);
    }

    bool Update() override {
        if (this->GetMainWindow() == nullptr) return false;
        if (glfwWindowShouldClose(GetMainWindow())) return false;

        processInput(GetMainWindow());
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program_);
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
    GLuint program_;
};

ENTRY_IMPLEMENT_MAIN(ExampleShader, "ExampleHelloTriangle",
                     "https://learnopengl.com/Getting-started/Shaders")
