#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "../include/glad/glad.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/glm/gtx/rotate_vector.hpp"
#include "../include/glm/gtx/vector_angle.hpp"
#include <GLFW/glfw3.h>

#include "shaderClass.h"

class Camera{
    public:
        // Stores the main three vectors used to find the position and orientation
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 cameraMatrix = glm::mat4(1.0f);

        // Prevents the camera from jumping around when first clicking left click
        bool firstClick = true;

        // Stores the width and height of the window
        int width;
        int height;

        // Adjust the speed of the camera and it's sensitivity when looking around
        float speed = 0.1f;
        float sensitivity = 100.0f;

        // Camera construction to set up initial values
        Camera(int width, int height, glm::vec3 position);

        // Updates the camera mastrix to the Vertex Shader
        void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
        // Exports the camera matrix to a shader
        void Matrix(Shader& shader, const char* uniform);
        // Handles camera inputs
        void Inputs(GLFWwindow* window);
};

#endif
