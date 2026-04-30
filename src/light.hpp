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
    void RenderLight(Camera& camera);
    void CleanUpLight();

   	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPosition = glm::vec3(0.5f, 0.0f, -3.0f);

private:
    Shader lightShader;
    VAO lightVAO;
    GLuint lightVBO;
    GLuint lightEBO;
};

#endif
