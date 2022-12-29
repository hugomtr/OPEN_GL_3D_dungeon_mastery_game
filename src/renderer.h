#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "model.h"
#include "camera.h"
#include "texture.h"
#include "monster.h"

#include <iostream>

struct WeaponsModel {
    Model sword;
    Model cudgel;
};

class Renderer {
public:
    Renderer(){
        camera = Camera::getInstance(); 
    };
    ~Renderer() = default;
    void renderMaze(Shader &shader,std::vector<std::vector<uint>> &texture_ids);
    void renderLava(Shader &lava_shader,std::vector<uint> &lava_tex_ids);
    void renderWeapons(Shader &shader,WeaponsModel & model);
    void renderRosettaStone(Shader &shader,Model &model3d);
    void renderFlasks(Shader &shader,Model &flask);
    void renderMonster(Shader &shader,Model &model_monster,Monster &monster);
    void renderCube();
    void renderQuad();
    void renderTestQuad();
private:
    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;
    unsigned int quadVAO = 0;
    unsigned int quadVBO = 0;
    Camera * camera;
};

#endif
