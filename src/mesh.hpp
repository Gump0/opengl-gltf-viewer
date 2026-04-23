#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>

#include "VAO.hpp"
#include "EBO.hpp"
#include "camera.hpp"
#include "texture.hpp"

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indicies;
    std::vector<Texture> textures;

    VAO vao;

    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indicies, std::vector<Texture>& textures);

    void Draw
    (
        Shader& shader,
        Camera& camera,
        glm::mat4 matrix = glm::mat4(1.0f),
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
    );
};

#endif
