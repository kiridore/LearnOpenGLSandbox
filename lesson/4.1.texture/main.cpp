#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stb_image.h>

#include "common/app.hpp"
#include "common/shader.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
    -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
};

unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
};

class ExampleShader : public Entry::AppI {
public:
    ExampleShader(std::string name, std::string desc)
        : Entry::AppI(name, desc),
          shader_("./asset/shader/4.1.texture_vert.glsl",
                  "./asset/shader/4.1.texture_frag.glsl") {}

    void Init() override {
        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(GetMainWindow(),
                                       framebuffer_size_callback);

        // VAO
        glGenVertexArrays(1, &VAO_);
        glBindVertexArray(VAO_);

        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        GLuint EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void *)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void *)(3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                              (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);

        glGenTextures(1, &tex_);
        glBindTexture(GL_TEXTURE_2D, tex_);

        // set the texture wrapping/filtering options (on the currently bound
        // texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        unsigned char *data =
            stbi_load("./asset/img/wall.jpg", &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load img" << std::endl;
        }
        stbi_image_free(data);
    }

    bool Update() override {
        if (this->GetMainWindow() == nullptr) return false;
        if (glfwWindowShouldClose(GetMainWindow())) return false;

        processInput(GetMainWindow());
        glClearColor(0.2f, 0.3f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindTexture(GL_TEXTURE_2D, tex_);
        shader_.Use();
        glBindVertexArray(VAO_);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        return true;
    }

    int Shutdown() override {
        glfwTerminate();
        return 0;
    }

private:
    GLuint VAO_;
    GLuint tex_;
    Shader shader_;
};

ENTRY_IMPLEMENT_MAIN(ExampleShader, "ExampleTexture",
                     "https://learnopengl.com/Getting-started/Textures")
