#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;  // stores data for normals
layout (location = 2) in vec3 aColor;   // stores color data from each vertices
layout (location = 3) in vec2 aTexture; // stores texture data

out vec3 currentPosition;   // output the current position for the fragment shader
out vec3 normal;            // output the normal for the fragment shader
out vec3 color;             // output vec3 parameter through name of "color"
out vec2 texCoord;          // output the texture coordinates to the fragment shader

uniform mat4 camMatrix;     // impports the camera matrix from the main function
uniform mat4 model;         // importsd the model matrix from the main function
uniform mat4 translation;   // imports mesh's imported translation
uniform mat4 rotation;      // imports mesh's rotation data
uniform mat4 scale;         // imports mesh's scale data

void main()
{
    mat4 modelFull = model * translation * rotation * scale;

    currentPosition = vec3(modelFull * vec4(aPos, 1.0));
    gl_Position = camMatrix * modelFull * vec4(aPos, 1.0f);

    // prevents lighting from breaking under non-uniform scaling
    normal = normalize(mat3(transpose(inverse(modelFull))) * aNormal);

    color = aColor;
    texCoord = aTexture;
};
