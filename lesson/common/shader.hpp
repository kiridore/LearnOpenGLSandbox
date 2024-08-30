#pragma once
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <string>

class Shader {
public:
    Shader(const char *vertex_path, const char *fragment_path);
    ~Shader() = default;

    void Use();

    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;

    GLuint ID;
private:
};
