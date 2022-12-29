#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/renderer.h"
#include "src/hero.h"
#include "src/monster.h"
#include "src/model.h"
#include "src/texture.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processchangeDirection(GLFWwindow *window);
void processInput(GLFWwindow *window);
void processMovement(GLFWwindow *window);
void show_gpu_memory(void);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Hero * hero = Hero::getInstance();
Camera * camera = Camera::getInstance();
Renderer renderer;

bool firstMouse = true;
float lastX =  SCR_WIDTH / 2.0f;
float lastY =  SCR_HEIGHT / 2.0;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Specifying that a pixels can contain 4 subsamples for anti aliasing 
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "DungeonMastery", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configure all OpenGL states
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    
    const GLubyte* vendor_mod = glGetString(GL_VENDOR); // Returns the vendor
    const GLubyte* renderer_mod = glGetString(GL_RENDERER); // Returns a hint to the model

    std::cout << "Running on GPU : " << vendor_mod << renderer_mod << std::endl;

    // build and compile our shader program
    // ------------------------------------
    Shader basic_shader("../shaders/basic_shader.vs", "../shaders/basic_shader.fs");
    Shader normal_parallax_shader("../shaders/normal_parallax_shader.vs", "../shaders/normal_parallax_shader.fs");
    Shader normal_specular_emission_shader("../shaders/normal_specular_emission_shader.vs", "../shaders/normal_specular_emission_shader.fs");
    Shader lavaShader("../shaders/lava_shader.vs", "../shaders/lava_shader.fs");

    // Render Loop
    // -----------
    Texture floorTex("../ressources/texture/ground_Color.jpg","../ressources/texture/ground_Normal.jpg","../ressources/texture/ground_Depth.jpg",GL_CLAMP_TO_EDGE);
    Texture cubeTex("../ressources/texture/Rock_Color.jpg","../ressources/texture/Rock_Normal.jpg","../ressources/texture/Rock_Depth.jpg",GL_CLAMP_TO_EDGE);
    Texture roofTex("../ressources/texture/roof_Color.jpg","../ressources/texture/roof_Normal.jpg","../ressources/texture/roof_Depth.jpg",GL_CLAMP_TO_EDGE);
    Texture lavaTex("../ressources/texture/Lava_Color.jpg","../ressources/texture/Lava_Normal.jpg","../ressources/texture/Lava_Depth.jpg",GL_CLAMP_TO_EDGE);
    std::vector<std::vector<uint>> texture_maze_ids{floorTex.ids,cubeTex.ids,roofTex.ids}; 
    
    Model monster_model("../ressources/models/vampire/dancing_vampire.dae");
    Model sword("../ressources/models/medieval-sword/model.dae");
    Model cudgel("../ressources/models/cudgel/NordsTenderizer_tilted.fbx");
    Model flask("../ressources/models/moon_potion_mask/flask.dae");
    Model rosetta("../ressources/models/rosetta-stone/scene.gltf");

    WeaponsModel weapons{sword,cudgel};

    float accumulateTimeHeroMovement = 0.0f;
    float accumulateTimeMonsterMovement = 0.0f;
    float accumulateTimeDirection = 0.0f;

    Map* map = Map::getInstance();

    std::vector<std::vector<int>> maze = map->getMap();

    std::vector<Monster> monsters_list;

    // create Monsters object
    for (int i = 0; i < map->n_rows; i++){
        for (int j = 0;j < map->n_columns; j++){
            if (maze[i][j] == 3){
                monsters_list.push_back(Monster(std::vector<int>{i,j}));
            }
        }
    }

    while(!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        processInput(window);

        float currentFrame = static_cast<float>(glfwGetTime());
        
        if (accumulateTimeHeroMovement > 0.3) {
            accumulateTimeHeroMovement = 0.0;
            processMovement(window);
        }

        if (accumulateTimeMonsterMovement > 1.0) {
            accumulateTimeMonsterMovement = 0.0;
            for (Monster & monster : monsters_list){
                monster.process_turn();
                if (monster.is_dead){
                    std::cout << "monster died" <<std::endl;
                    deleteMonster(monsters_list, monster.initial_position);
                }
            }
        }        
        
        if (accumulateTimeDirection > 0.25) {
            accumulateTimeDirection = 0.0;
            processchangeDirection(window);
        }

        deltaTime = currentFrame - lastFrame;
        accumulateTimeDirection += deltaTime;
        accumulateTimeMonsterMovement += deltaTime;
        accumulateTimeHeroMovement += deltaTime;
        lastFrame = currentFrame;

        if ((hero->STAMINA + deltaTime) < 1)
            hero->STAMINA += deltaTime;
        // input
        // -----
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        renderer.renderMaze(normal_parallax_shader,texture_maze_ids);
        renderer.renderFlasks(normal_specular_emission_shader,flask);
        renderer.renderLava(lavaShader,lavaTex.ids);
        for (Monster & monster : monsters_list){
            renderer.renderMonster(normal_specular_emission_shader,monster_model,monster);
        }
        renderer.renderRosettaStone(basic_shader,rosetta);
        renderer.renderWeapons(normal_specular_emission_shader,weapons);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glfwTerminate();    
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void processchangeDirection(GLFWwindow *window)
{
    // clavier direction
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT);
}

void processMovement(GLFWwindow *window) {
    hero->process_turn();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera->process_movement();
        hero->process_input_user();
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (hero->STAMINA > hero->getWeapon()->stamina_needed)
            hero->attack_monster();
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        hero->should_change_weapon();
        std::cout << hero->weapon_type << std::endl;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void show_gpu_memory(){
    GLint total_memory, available_memory;
    glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &total_memory);
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &available_memory);

    std::cout << "Total GPU memory: %d MB\n" <<  total_memory / (1024) << std::endl;
    std::cout << "Available GPU memory: %d MB\n" << available_memory / (1024) << std::endl;
}