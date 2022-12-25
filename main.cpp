#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/shader.h"
#include "src/camera.h"
#include "src/model.h"
#include "src/map.h"
#include "src/renderer.h"
#include "src/texture.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void processMovement(GLFWwindow *window);
unsigned int loadTexture(const char* filename,GLint mode);
void show_gpu_memory(void);

// camera
Camera camera;



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
    glfwSetCursorPosCallback(window, mouse_callback);
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
    float accumulateTime = 0.0;

    Texture floorTex("../ressources/texture/ground_Color.jpg","../ressources/texture/ground_Normal.jpg","../ressources/texture/ground_Depth.jpg",GL_CLAMP_TO_EDGE);
    Texture cubeTex("../ressources/texture/Rock_Color.jpg","../ressources/texture/Rock_Normal.jpg","../ressources/texture/Rock_Depth.jpg",GL_CLAMP_TO_EDGE);
    Texture roofTex("../ressources/texture/roof_Color.jpg","../ressources/texture/roof_Normal.jpg","../ressources/texture/roof_Depth.jpg",GL_CLAMP_TO_EDGE);
    Texture lavaTex("../ressources/texture/Lava_Color.jpg","../ressources/texture/Lava_Normal.jpg","../ressources/texture/Lava_Depth.jpg",GL_CLAMP_TO_EDGE);
    std::vector<std::vector<uint>> texture_maze_ids{floorTex.ids,cubeTex.ids,roofTex.ids}; 
    
    Model vampire("../ressources/models/vampire/dancing_vampire.dae");
    Model sword("../ressources/models/medieval-sword/model.dae");
    Model cudgel("../ressources/models/cudgel/NordsTenderizer_tilted.fbx");
    Model flask("../ressources/models/moon_potion_mask/flask.dae");

    Weapons weapons{sword,cudgel};

    Model rosetta("../ressources/models/rosetta-stone/scene.gltf");

    while(!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        processInput(window);
        processMovement(window);

        float currentFrame = static_cast<float>(glfwGetTime());
        if (accumulateTime > 0.2) {
            show_gpu_memory();
            accumulateTime = 0.0;
        }
        deltaTime = currentFrame - lastFrame;
        accumulateTime += deltaTime;
        lastFrame = currentFrame;

        // input
        // -----
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Renderer renderer(camera);
        renderer.renderMaze(normal_parallax_shader,texture_maze_ids);
        renderer.renderFlasks(normal_specular_emission_shader,flask);
        renderer.renderLava(lavaShader,lavaTex.ids);
        renderer.renderMonsters(normal_specular_emission_shader,vampire);
        renderer.renderRosettaStone(basic_shader,rosetta);

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

// void processMovement(GLFWwindow *window)
// {
//     // clavier mouvement
//     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//         camera.ProcessKeyboard(FORWARD);
//     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//         camera.ProcessKeyboard(BACKWARD);
//     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//         camera.ProcessKeyboard(LEFT);
//     if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//         camera.ProcessKeyboard(RIGHT);
// }

void processMovement(GLFWwindow *window)
{
  // clavier mouvement
    float cameraSpeed = 0.3f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.Position += cameraSpeed * camera.Front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.Position -= cameraSpeed * camera.Front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.Position -= glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.Position += glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;   

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset,yoffset,true);
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
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void show_gpu_memory(){
    GLint total_memory, available_memory;
    glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &total_memory);
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &available_memory);

    std::cout << "Total GPU memory: %d MB\n" <<  total_memory / (1024) << std::endl;
    std::cout << "Available GPU memory: %d MB\n" << available_memory / (1024) << std::endl;
}