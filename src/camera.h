#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "map.h"
#include "textRenderer.h"

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.05f;
const float ZOOM        =  50.0f;

// perpective value
const float NEAR = 0.1f; 
const float FAR  = 100.0f;

// settings screen for projection matrix
const unsigned int SCR_WIDTH = 1980;
const unsigned int SCR_HEIGHT = 1080;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
protected:
    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(2.0f, 0.8f, 106.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(1.0f, 0.0f, 0.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors(false);
    }

    static Camera * camera;
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    glm::vec3 lightColor = glm::vec3(1.0f,1.0f,1.0f);
    std::vector<int> cameraMapCoordinates = {0,26};
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float vision_coeff = 50.0f;
    // get Instance of Camera
    static Camera * getInstance();
    void operator=(Camera & _other) = delete;
    Camera(Camera & _other) = delete;

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    glm::mat4 GetProjectionMatrix(float ratio_viewport = (float)SCR_WIDTH/(float)SCR_HEIGHT)
    {
        return glm::perspective(glm::radians(Zoom), ratio_viewport, NEAR, FAR);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction)
    {
        if (direction == BACKWARD){
            Front = -Front;
            this->updateCameraVectors(true);}

        if (direction == LEFT){
            Front = -Right;
            this->updateCameraVectors(true);}            

        if (direction == RIGHT){
            Front = Right;
            updateCameraVectors(true);}
    }

    void process_movement(){
        Map* map = Map::getInstance();
        std::vector<std::vector<int>> maze = map->getMap();
        const float velocity = 4.0f;

        int x = static_cast<int>(cameraMapCoordinates[0] + Front[0]);
        int y = static_cast<int>(cameraMapCoordinates[1] + Front[2]);

        if ((x < 30) && (y < 30) && (x >= 0) && (y >= 0)){
            if (maze[x][y] > 0){
                Position += Front * velocity;
                cameraMapCoordinates[0] = x;
                cameraMapCoordinates[1] = y;
            }
        }
    }

    // // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    // void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true,GLboolean constrainYaw = true)
    // {
    //     xoffset *= MouseSensitivity;
    //     yoffset *= MouseSensitivity;

    //     Pitch += yoffset;

    //     // make sure that when pitch is out of bounds, screen doesn't get flipped
    //     if (constrainPitch)
    //     {
    //         if (Pitch > 89.0f)
    //             Pitch = 89.0f;
    //         if (Pitch < -89.0f)
    //             Pitch = -89.0f;
    //     }
    //     updateCameraVectors(false);
    // }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f; 
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors(bool movement)
    {
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};

#endif