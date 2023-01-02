#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <map>
#include <string>

#include "shader.h"
#include "camera.h"

struct Character {
    unsigned int TextureID; // ID of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class TextRenderer {
    std::map<GLchar, Character> Characters;
    FT_Library font;
    FT_Face face;
    GLuint QuadVAO;
    GLuint QuadVBO;
    Shader * text_shader = new Shader("../shaders/text_shader.vs","../shaders/text_shader.fs");
    void fillCharacters();
    void configuringQuad();
public:
    TextRenderer(const char* path_to_font = "../ressources/font/Antonio-Bold.ttf");
    void display(std::string text, float x, float y, float scale, glm::vec3 color);
    ~TextRenderer(){
        glDeleteProgram(text_shader->ID);}
};

#endif