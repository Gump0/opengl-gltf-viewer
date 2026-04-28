#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

// #include <glm/glm.hpp>

#include "shaderClass.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include "camera.hpp"

class Light
{
public:
    Light();
    void InitializeLight();
    void RenderLight(Camera& camera, glm::vec3 lightPosition);
    void CleanUpLight();
private:
    Shader lightShader;
    VAO lightVAO;
    GLuint lightVBO;
    GLuint lightEBO;
};

#endif
