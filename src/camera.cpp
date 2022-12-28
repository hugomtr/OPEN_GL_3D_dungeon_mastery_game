#include "camera.h"

Camera* Camera::camera = nullptr;

Camera * Camera::getInstance()
{
    if (camera == nullptr){
        camera = new Camera();
    }
    return camera;
}