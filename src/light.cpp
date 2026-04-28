#include <vector>
#include "light.hpp"

std::vector<GLuint> lightIndices =
{
    0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

std::vector<GLfloat> lightVertices =
{
    -0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

Light::Light() { } // pre-define constructor to prevent linker errors

void Light::InitializeLight()
{
    lightShader = Shader("shaders/light.vert", "shaders/light.frag");

    lightVAO.Bind();

    // manually create and upload the vbo
    glGenBuffers(1, &lightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, lightVertices.size() * sizeof(float), lightVertices.data(), GL_STATIC_DRAW);


    // manually create and upload the ebo
    glGenBuffers(1, &lightEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, lightIndices.size() * sizeof(GLuint), lightIndices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    lightVAO.Unbind();
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    lightShader.Activate();
}

void Light::RenderLight(Camera& camera, glm::vec3 lightPosition)
{
    lightShader.Activate();

    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPosition);
    glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));

    camera.Matrix(lightShader, "camMatrix");
    lightVAO.Bind();
    glDrawElements(GL_TRIANGLES, lightIndices.size(), GL_UNSIGNED_INT, 0);
}

void Light::CleanUpLight()
{
    // cleanup light object dependencies
    lightVAO.Delete();
    lightShader.Delete();
}
