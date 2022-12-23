#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>

#include <iostream>

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
    Texture() = default;
    Texture(const char* filename,GLint mode);
    ~Texture() = default;
};

#endif