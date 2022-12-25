#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "texture.h"
#include "map.h"
#include "model.h"

#include <iostream>

struct Weapons {
    Model sword;
    Model cudgel;
};

class Renderer {
public:
    Renderer(Camera & _camera): camera(_camera) {};
    ~Renderer() = default;
    void renderMaze(Shader &shader,std::vector<std::vector<uint>> &texture_ids);
    void renderLava(Shader &lava_shader,std::vector<uint> &lava_tex_ids);
    void renderWeapons(Shader &shader,Weapons & weapons);
    void renderRosettaStone(Shader &shader,Model &model3d);
    void renderFlasks(Shader &shader,Model &flask);
    void renderMonsters(Shader &shader,Model &monster);
    void renderCube();
    void renderQuad();
    void renderTestQuad();
private:
    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;
    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;
    Camera camera;
};

#endif
