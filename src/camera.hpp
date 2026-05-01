#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.hpp"

class Camera
{
    public:
        glm::vec3 position;
        glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::mat4 cameraMatrix = glm::mat4(1.0f);
        const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        uint width;
        uint height;

        float speed = releasedSpeed;
        const float releasedSpeed = 0.03f;
        const float shiftSpeed = 0.15f;
        const float sensitivity = 100.0f;

        Camera(glm::vec3 position, uint width, uint height);

        void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
        void Matrix(Shader& shader, const char* uniform);
        void Inputs(GLFWwindow* window);

        bool firstClick = true;
        double lastMouseX = 0.0;
        double lastMouseY = 0.0;
};

#endif
