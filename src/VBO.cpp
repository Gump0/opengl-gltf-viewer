#include "VBO.hpp"

// constructor that generates a vertex buffer object and links it to vertices
VBO::VBO(std::vector<Vertex>& vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

// binds the vbo
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// unbinds the vbo
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// deletes the vbo
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
