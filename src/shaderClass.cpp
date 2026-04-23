#include "shaderClass.hpp"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertSrc = ReadFile(vertexFile);
    std::string fragSrc = ReadFile(fragmentFile);

    const char* vertexSource   = vertSrc.c_str();
    const char* fragmentSource = fragSrc.c_str();

    // vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    CompileErrors(vertexShader, "VERTEX");

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << '\n';
    }

    // fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    CompileErrors(fragmentShader, "FRAGMENT");

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment shader compilation failed:\n" << infoLog << '\n';
    }

    // shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << '\n';
    }

    // delete the now useless vert and frag shader.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(shaderProgram);
}

void Shader::Delete()
{
    glDeleteProgram(shaderProgram);
}

void Shader::CompileErrors(uint shader, const char* type)
{
    GLint hasCompiled;
    char infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if(hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for : " << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if(hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
    }
}

std::string Shader::ReadFile(std::string path)
{
    std::string content = "";

    std::ifstream file(path);
    // check if file is opening
    if(!file.is_open())
    {
        std::cerr << "Failed to open file cuh: " << path << std::endl;
        return content;
    }

    std::string line;
    while(std::getline(file, line))
    {
        content += line + "\n";
    }
    file.close();

    return content;
}
