#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

class Shader
{
    public:
        GLuint shaderProgram;
        Shader(const char* vertexFile, const char* fragmentFile);

        void Activate();
        void Delete();

    private:
        void compileErrors(uint shader, const char* type);
        std::string readFile(std::string path);
};

#endif
