#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

struct Texture {
    uint id;
    uint normal_id;
    uint depth_id;
    std::vector<uint> ids;
    std::string type;
    std::string path;
    Texture() = default;
    Texture(const char* filename,GLint mode = GL_CLAMP_TO_EDGE);
    Texture(const char* filename1,const char* filename2,const char* filename3,GLint mode);
    ~Texture() = default;
};



#endif