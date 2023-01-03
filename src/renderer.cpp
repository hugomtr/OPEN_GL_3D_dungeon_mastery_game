#include "renderer.h"

void triangle_tangent_calc(glm::vec3 pos1,glm::vec3 pos2,glm::vec3 pos3,glm::vec2 uv1,glm::vec2 uv2,glm::vec2 uv3,glm::vec3 &tangent){
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
    
    tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
}

float calculate_rotation_monster(const std::vector<int>& direction) {
    //
    if (direction == std::vector<int>{0,-1})
        return 180.0f;
    if (direction == std::vector<int>{1,0})
        return 90.0f;
    if (direction == std::vector<int>{-1,0})
        return -90.0f;
    return 0.0f;
}

float calculate_rotation_weapon(const float a,const float b) {
    float value_rot_y = 0.0f;

    if ((a == -1.0f) && (b == 0.0f))
        value_rot_y = 180.0f;

    if ((a == 0.0f) && (b == 1.0f)) 
        value_rot_y = -90.0f;

    if ((a == 0.0f) && (b == -1.0f)) 
        value_rot_y = 90.0f;

    return value_rot_y; 
}

glm::vec3 calculate_rotation_cudgel(const std::vector<int>& direction) {
    if (direction == std::vector<int>{1,0})
        return glm::vec3(30.0f,-30.0f,-135.0f);
    // if (direction == std::vector<int>{-1,0})
    //     return;
    // if (direction == std::vector<int>{0,-1})
    //     return 180.0f;
    // if (direction == std::vector<int>{1,0})
    //     return 90.0f;
}

// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
void Renderer::renderCube()
{
    // initialize (if necessary)
    if (cubeVAO == 0)
    {
        glm::vec3 tangent1,tangent2,tangent3,tangent4,tangent5,tangent6,tangent7,tangent8,tangent9,tangent10,tangent11,tangent12;
        triangle_tangent_calc(glm::vec3(-1.0f, -1.0f, -1.0f),glm::vec3(1.0f,  1.0f, -1.0f),glm::vec3(1.0f, -1.0f, -1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,1.0f),glm::vec2(1.0f,0.0f),tangent1);
        triangle_tangent_calc(glm::vec3(1.0f,  1.0f, -1.0f),glm::vec3(-1.0f, -1.0f, -1.0f),glm::vec3(-1.0f,  1.0f, -1.0f),glm::vec2(1.0f, 1.0f),glm::vec2(0.0f, 0.0f),glm::vec2(0.0f, 1.0f),tangent2);
        triangle_tangent_calc(glm::vec3(-1.0f, -1.0f,  1.0f),glm::vec3(1.0f, -1.0f,  1.0f),glm::vec3(1.0f,  1.0f,  1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),tangent3);
        triangle_tangent_calc(glm::vec3( 1.0f,  1.0f,  1.0f),glm::vec3(-1.0f,  1.0f,  1.0f),glm::vec3(-1.0f, -1.0f,  1.0f),glm::vec2(1.0f,1.0f),glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),tangent4);
        triangle_tangent_calc(glm::vec3(-1.0f,  1.0f,  1.0f),glm::vec3(-1.0f,  1.0f, -1.0f),glm::vec3(-1.0f, -1.0f, -1.0f),glm::vec2(1.0f,1.0f),glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),tangent5);
        triangle_tangent_calc(glm::vec3(-1.0f, -1.0f, -1.0f),glm::vec3(-1.0f, -1.0f,  1.0f),glm::vec3(-1.0f,  1.0f,  1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),tangent6);
        triangle_tangent_calc(glm::vec3(1.0f,  1.0f,  1.0f),glm::vec3(1.0f, -1.0f, -1.0f),glm::vec3(1.0f,  1.0f, -1.0f),glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),tangent7);
        triangle_tangent_calc(glm::vec3(1.0f, -1.0f, -1.0f),glm::vec3(1.0f,  1.0f,  1.0f),glm::vec3(1.0f, -1.0f,  1.0f),glm::vec2(1.0f,0.0f),glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),tangent8);
        triangle_tangent_calc(glm::vec3(-1.0f, -1.0f, -1.0f),glm::vec3(1.0f, -1.0f, -1.0f),glm::vec3(1.0f, -1.0f, 1.0f),glm::vec2(1.0f,1.0f),glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),tangent9);
        triangle_tangent_calc(glm::vec3(1.0f, -1.0f, 1.0f),glm::vec3(-1.0f, -1.0f, 1.0f),glm::vec3(-1.0f, -1.0f, -1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),tangent10);
        triangle_tangent_calc(glm::vec3(-1.0f, 1.0f, -1.0f),glm::vec3(1.0f,  1.0f, 1.0f),glm::vec3(1.0f, 1.0f, -1.0f),glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),tangent11);
        triangle_tangent_calc(glm::vec3(1.0f, 1.0f, 1.0f),glm::vec3(-1.0f,  1.0f, -1.0f),glm::vec3(-1.0f, 1.0f, 1.0f),glm::vec2(1.0f,0.0f),glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),tangent12);

        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, tangent1.x, tangent1.y, tangent1.z,// bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, tangent1.x, tangent1.y, tangent1.z,// top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, tangent1.x, tangent1.y, tangent1.z,// bottom-right    

             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, tangent2.x, tangent2.y, tangent2.z,// top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, tangent2.x, tangent2.y, tangent2.z,// bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, tangent2.x, tangent2.y, tangent2.z,// top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, tangent3.x, tangent3.y, tangent3.z,// bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, tangent3.x, tangent3.y, tangent3.z,// bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, tangent3.x, tangent3.y, tangent3.z,// top-right

             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, tangent4.x, tangent4.y, tangent4.z,// top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, tangent4.x, tangent4.y, tangent4.z,// top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, tangent4.x, tangent4.y, tangent4.z,// bottom-left
            // left face

            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, tangent5.x, tangent5.y, tangent5.z,// top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, tangent5.x, tangent5.y, tangent5.z,// top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, tangent5.x, tangent5.y, tangent5.z,// bottom-left

            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, tangent6.x, tangent6.y, tangent6.z,// bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, tangent6.x, tangent6.y, tangent6.z,// bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, tangent6.x, tangent6.y, tangent6.z,// top-right
            // right face

             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, tangent7.x, tangent7.y, tangent7.z,// top-left
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, tangent7.x, tangent7.y, tangent7.z,// bottom-right
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, tangent7.x, tangent7.y, tangent7.z,// top-right   
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, tangent8.x, tangent8.y, tangent8.z,// bottom-right
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, tangent8.x, tangent8.y, tangent8.z,// top-left
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, tangent8.x, tangent8.y, tangent8.z,// bottom-left     
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, tangent9.x, tangent9.y, tangent9.z,// top-right
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, tangent9.x, tangent9.y, tangent9.z,// top-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, tangent9.x, tangent9.y, tangent9.z,// bottom-left

             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, tangent10.x, tangent10.y, tangent10.z,// bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, tangent10.x, tangent10.y, tangent10.z,// bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, tangent10.x, tangent10.y, tangent10.z,// top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, tangent11.x, tangent11.y, tangent11.z,// top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, tangent11.x, tangent11.y, tangent11.z,// bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, tangent11.x, tangent11.y, tangent11.z,// top-right   

             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, tangent12.x, tangent12.y, tangent12.z,// bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, tangent12.x, tangent12.y, tangent12.z,// top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, tangent12.x, tangent12.y, tangent12.z,// bottom-left        
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        // tangent coord attribute
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}


void Renderer::renderQuad()
{
    if (quadVAO == 0)
    {
        glm::vec3 tangent1,tangent2;
        triangle_tangent_calc(glm::vec3(-1.0f, 0.0f, 1.0f),glm::vec3(-1.0f,  0.0f, -1.0f),glm::vec3(1.0f, 0.0f, -1.0f),glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),tangent1);
        triangle_tangent_calc(glm::vec3(-1.0f,  0.0f, 1.0f),glm::vec3(1.0f, 0.0f, -1.0f),glm::vec3(1.0f,  0.0f, 1.0f),glm::vec2(0.0f, 1.0f),glm::vec2(1.0f, 0.0f),glm::vec2(1.0f, 1.0f),tangent2);    
    
        float quadVertices[] = {
            // positions      // normal         // texture Coords
            -1.0f,0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, tangent1.x, tangent1.y, tangent1.z,
            -1.0f,0.0f,-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, tangent1.x, tangent1.y, tangent1.z,
            1.0f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f,1.0f, 0.0f, tangent1.x, tangent1.y, tangent1.z,

            -1.0f,0.0f, 1.0f, 0.0f, 1.0f, 0.0f,0.0f, 1.0f, tangent2.x, tangent2.y, tangent2.z,
            1.0f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, tangent2.x, tangent2.y, tangent2.z,
            1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, tangent2.x, tangent2.y, tangent2.z,
        };
        
    // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        // tangent coord attribute
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

// by convention textures_list will be order given the following 
// 
void Renderer::renderMaze(Shader &shader,std::vector<std::vector<uint>> &texture_ids)
{
    Map* map = Map::getInstance();

    std::vector<std::vector<int>> maze = map->getMap();

    glm::mat4 model,view,projection;
    view = camera->GetViewMatrix();
    projection = camera->GetProjectionMatrix();

    std::vector<uint> floorTexIds = texture_ids[0];
    std::vector<uint> cubeTexIds = texture_ids[1];
    std::vector<uint> roofTexIds = texture_ids[2];

    shader.use();
    shader.setInt("diffuseMap", 0);
    shader.setInt("normalMap", 1);
    shader.setInt("depthMap", 2);

    shader.setMat4f("projection", glm::value_ptr(projection));
    shader.setMat4f("view", glm::value_ptr(view));

    shader.setVec3("viewPos", glm::value_ptr(this->camera->Position));
    shader.setVec3("lightPos", glm::value_ptr(this->camera->Position));

    shader.setVec3("lightColor", glm::value_ptr(camera->lightColor));

    shader.setFloat("height_scale", 0.1f);
    shader.setFloat("vision_coeff", camera->vision_coeff);


    // block inside
    for(int i = 0; i < map->n_rows; i++){
        for (int j = 0;j < map->n_columns; j++){
            if (maze[i][j] <= 0){
                glEnable(GL_CULL_FACE);
                model = glm::mat4(1.0f);
                model = glm::scale(model, glm::vec3(2.0f));
                model = glm::translate(model,glm::vec3(static_cast<float>(2*i+1),0.0f,static_cast<float>(2*j+1)));
                shader.setMat4f("model", glm::value_ptr(model));
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, cubeTexIds[0]);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, cubeTexIds[1]);
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, cubeTexIds[2]);
                this->renderCube();
                glDisable(GL_CULL_FACE);
            } else {
                if (maze[i][j] != 5){
                    // In case this is not lava
                    // ground 
                    model = glm::mat4(1.0f);
                    model = glm::scale(model, glm::vec3(2.0f));
                    model = glm::translate(model,glm::vec3(static_cast<float>(2*i+1),-1.0f,static_cast<float>(2*j+1)));
                    shader.setMat4f("model", glm::value_ptr(model));
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, floorTexIds[0]);
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, floorTexIds[1]);
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, floorTexIds[2]);
                    this->renderQuad();
                }
                // roof
                model = glm::mat4(1.0f);
                model = glm::scale(model, glm::vec3(2.0f));
                model = glm::translate(model,glm::vec3(static_cast<float>(2*i+1),1.0f,static_cast<float>(2*j+1)));
                model = glm::rotate(model,glm::radians(180.0f),glm::vec3(1.0f,0.0f,0.0f));
                shader.setMat4f("model", glm::value_ptr(model));
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, roofTexIds[0]);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, roofTexIds[1]);
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, roofTexIds[2]);
                this->renderQuad();
            }     
        }
    }
}

void Renderer::renderLava(Shader &lava_shader,std::vector<uint> &lavaTexIds)
{
    Map* map = Map::getInstance();

    std::vector<std::vector<int>> maze = map->getMap();

    glm::mat4 model,view,projection;
    view = camera->GetViewMatrix();
    projection = camera->GetProjectionMatrix();

    glm::vec3 lavaColor(1.0f,0.9f,0.9f);

    lava_shader.use();
    lava_shader.setInt("diffuseMap", 0);
    lava_shader.setInt("normalMap", 1);
    lava_shader.setInt("depthMap", 2);

    lava_shader.setMat4f("projection", glm::value_ptr(projection));
    lava_shader.setMat4f("view", glm::value_ptr(view));

    lava_shader.setVec3("viewPos", glm::value_ptr(this->camera->Position));
    lava_shader.setVec3("lightPos", glm::value_ptr(this->camera->Position));

    lava_shader.setVec3("lightColor", glm::value_ptr(lavaColor));

    lava_shader.setFloat("height_scale", 0.1f);
    lava_shader.setFloat("vision_coeff", 2*camera->vision_coeff);

    // block inside
    for(int i = 0; i < map->n_rows; i++){
        for (int j = 0;j < map->n_columns; j++){
            if (maze[i][j] == 5){
                // ground 
                model = glm::mat4(1.0f);
                model = glm::scale(model, glm::vec3(2.0f));
                model = glm::translate(model,glm::vec3(static_cast<float>(2*i+1),-1.0f,static_cast<float>(2*j+1)));
                lava_shader.setMat4f("model", glm::value_ptr(model));
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, lavaTexIds[0]);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, lavaTexIds[1]);
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, lavaTexIds[2]);
                this->renderQuad();
            }     
        }
    }
}

void Renderer::renderTestQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions              
            -1.0f,0.0f, 1.0f,
            -1.0f,0.0f,-1.0f, 
            1.0f, 0.0f,-1.0f, 

            -1.0f,0.0f, 1.0f, 
            1.0f, 0.0f,-1.0f, 
            1.0f, 0.0f, 1.0f, 
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


void Renderer::renderRosettaStone(Shader &shader,Model &model3d)
{
    Map* map = Map::getInstance();

    float idx_rows = map->coords_rosetta[0];
    float idx_columns = map->coords_rosetta[1];

    glm::mat4 model,view,projection;
    view = camera->GetViewMatrix();
    projection = camera->GetProjectionMatrix();

    shader.use();
    shader.setInt("diffuseMap", 0);
    shader.setMat4f("projection", glm::value_ptr(projection));
    shader.setMat4f("view", glm::value_ptr(view));

    shader.setVec3("viewPos", glm::value_ptr(this->camera->Position));
    shader.setVec3("lightPos", glm::value_ptr(this->camera->Position));
    shader.setVec3("lightColor", glm::value_ptr(camera->lightColor));

    // rosetta
    model = glm::mat4(1.0f);
    model = glm::translate(model,glm::vec3(static_cast<float>(4*(idx_rows+1)+1),0.6f,static_cast<float>(4*idx_columns)-1));
    model = glm::scale(model, glm::vec3(0.25f));
    model = glm::rotate(model, glm::radians(80.0f),glm::vec3(1.0f,0.0f,0.0f));
    model = glm::rotate(model, glm::radians(7.0f),glm::vec3(0.0f,1.0f,0.0f));
    shader.setMat4f("model", glm::value_ptr(model));
    model3d.Draw(shader);
}

// A terme utiliser des objets vampires qui auront une position (plus besoin de l'objet map?)
// une direction (pour les rotations la tete aligenr dans la bonne direction etc...)
void Renderer::renderMonster(Shader &shader,Model &model_monster,Monster & monster)
{
    glm::mat4 model,view,projection;
    view = camera->GetViewMatrix();
    projection = camera->GetProjectionMatrix();

    shader.use();
    shader.setInt("diffuseMap", 0);
    shader.setInt("specularMap", 1);
    shader.setInt("normalMap", 2);
    shader.setInt("emissionMap", 3);

    shader.setMat4f("projection", glm::value_ptr(projection));
    shader.setMat4f("view", glm::value_ptr(view));

    shader.setVec3("viewPos", glm::value_ptr(this->camera->Position));
    shader.setVec3("lightPos", glm::value_ptr(this->camera->Position));
    shader.setVec3("lightColor", glm::value_ptr(camera->lightColor));

    shader.setFloat("vision_coeff", camera->vision_coeff);

    // Vampire
    float i = monster.curr_position[0];
    float j = monster.curr_position[1];
    model = glm::mat4(1.0f);
    float scale_value = 0.018f;
    model = glm::translate(model,glm::vec3(static_cast<float>(4*i+2),-2.0f,static_cast<float>(4*j+2)));
    model = glm::scale(model, glm::vec3(scale_value));
    model = glm::rotate(model, glm::radians(calculate_rotation_monster(monster.direction)),glm::vec3(0.0f,1.0f,0.0f));    
    shader.setMat4f("model", glm::value_ptr(model));
    model_monster.Draw(shader);
}

// A terme utiliser des objets flask
void Renderer::renderFlasks(Shader &shader,Model &flask)
{
    Map* map = Map::getInstance();

    std::vector<std::vector<int>> maze = map->getMap();

    glm::mat4 model,view,projection;
    view = camera->GetViewMatrix();
    projection = camera->GetProjectionMatrix();

    shader.use();
    shader.setInt("diffuseMap", 0);
    shader.setInt("specularMap", 1);
    shader.setInt("normalMap", 2);
    shader.setInt("emissionMap", 3);

    shader.setMat4f("projection", glm::value_ptr(projection));
    shader.setMat4f("view", glm::value_ptr(view));

    shader.setVec3("viewPos", glm::value_ptr(this->camera->Position));
    shader.setVec3("lightPos", glm::value_ptr(this->camera->Position));
    shader.setVec3("lightColor", glm::value_ptr(camera->lightColor));

    shader.setFloat("vision_coeff", camera->vision_coeff);

    // objects inside
    for(int i = 0; i < map->n_rows; i++){
        for (int j = 0;j < map->n_columns; j++){
            if (maze[i][j] == 4){
                // flask     
                model = glm::mat4(1.0f);
                model = glm::translate(model,glm::vec3(static_cast<float>(4*i+2),-1.0f,static_cast<float>(4*j+2)));
                model = glm::rotate(model, glm::radians(-90.0f),glm::vec3(1.0f,0.0f,0.0f));
                shader.setMat4f("model", glm::value_ptr(model));
                flask.Draw(shader);
            }
        }
    }
}

void Renderer::renderWeapons(Shader &shader,WeaponsModel & model_weapon)
{
    Hero * hero = Hero::getInstance();

    glm::mat4 model,view,projection;
    view = camera->GetViewMatrix();
    projection = camera->GetProjectionMatrix();

    shader.use();
    shader.setInt("diffuseMap", 0);
    shader.setInt("specularMap", 1);
    shader.setInt("normalMap", 2);
    shader.setInt("emissionMap", 3);

    shader.setMat4f("projection", glm::value_ptr(projection));
    shader.setMat4f("view", glm::value_ptr(view));

    shader.setVec3("viewPos", glm::value_ptr(this->camera->Position));
    shader.setVec3("lightPos", glm::value_ptr(this->camera->Position));
    shader.setVec3("lightColor", glm::value_ptr(camera->lightColor));

    shader.setFloat("vision_coeff", camera->vision_coeff);

    // sword
    if (hero->weapon_type == SWORD){
        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(static_cast<float>(camera->Position[0] + 0.4*(camera->Front[0])),camera->Position[1],static_cast<float>(camera->Position[2] + 0.4*(camera->Front[2]))));
        model = glm::scale(model, glm::vec3(0.4f));

        float rotation_sword = calculate_rotation_weapon(camera->Front[0],camera->Front[2]);
        
        // Order is important here
        model = glm::rotate(model, glm::radians(rotation_sword),glm::vec3(0.0f,1.0f,0.0f));

        model = glm::rotate(model, glm::radians(-135.0f),glm::vec3(0.0f,0.0f,1.0f));
        model = glm::rotate(model, glm::radians(-30.0f),glm::vec3(0.0f,1.0f,0.0f));
        model = glm::rotate(model, glm::radians(30.0f),glm::vec3(1.0f,0.0f,0.0f));

        shader.setMat4f("model", glm::value_ptr(model));
        model_weapon.sword.Draw(shader);
    } else if (hero->weapon_type == CUDGEL) {
        // cudgel
        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(static_cast<float>(camera->Position[0] + 0.3*(camera->Front[0])),camera->Position[1],static_cast<float>(camera->Position[2] + 0.3*(camera->Front[2]))));
        model = glm::scale(model, glm::vec3(0.02f));
        
        float rotation_cudgel = calculate_rotation_weapon(camera->Front[0],camera->Front[2]);
        
        // Order is important here
        model = glm::rotate(model, glm::radians(rotation_cudgel),glm::vec3(0.0f,1.0f,0.0f));

        model = glm::rotate(model, glm::radians(-25.0f),glm::vec3(0.0f,0.0f,1.0f));
        model = glm::rotate(model, glm::radians(30.0f),glm::vec3(0.0f,1.0f,0.0f));
        
        shader.setMat4f("model", glm::value_ptr(model));
        model_weapon.cudgel.Draw(shader);
    }
}