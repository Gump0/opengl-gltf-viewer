#include "mesh.hpp"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indicies, std::vector<Texture>& textures)
{
    Mesh::vertices = vertices;
    Mesh::indicies = indicies;
    Mesh::textures = textures;

    vao.Bind();

    // generate vertex buffer object and links it to vertices
    VBO vbo(vertices);
    // generate element buffer array and link it with indicies
    EBO ebo(indicies);

    // link VBO and VAO
    // second parameter effects what layout or "layer" (look to default.vert for details)
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position)); // position (vec3)
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));   // normal (vec3)
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));    // color (vec3)
    vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texUV));    // texture (vec2)
    // unbind all to prevent accidently modifying them.
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Mesh::Draw
(
	Shader& shader,
	Camera& camera,
	glm::mat4 matrix,
	glm::vec3 translation,
	glm::quat rotation,
	glm::vec3 scale
)
{
    shader.Activate();
    vao.Bind();

    uint numDiffuse = 0;
    uint numSpecular = 0;

    for(uint i = 0; i < textures.size(); i++)
    {
        std::string num;
        std::string type = textures[i].type;
        if(type == "diffuse")
        {
            num = std::to_string(numDiffuse++);
        }
        else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }
        textures[i].TexUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }
    glUniform3f(glGetUniformLocation(shader.shaderProgram, "cameraPosition"), camera.position.x, camera.position.y, camera.position.z);
    camera.Matrix(shader, "camMatrix");

    // initialize matrices
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	// transform the matrices to their correct form
	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// push the matrices to the vertex shader
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
}
