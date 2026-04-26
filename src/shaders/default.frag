#version 330 core

out vec4 FragColor;         // outputs the colors in RGBA

                            /* NOTE: uniform and input variables (in/uniform variables)
                                are CASE SENSITIVE */

in vec3 currentPosition;    // imports the current position from the vertex shdader
in vec3 color;              // link vec3 color parameter from vertex shader
in vec2 texCoord;           // impports the texture coordinates to the vertex shader
in vec3 normal;             // imports the normal from the vertext shader cuh

uniform sampler2D diffuse0; // gets the texture unit from the main function
uniform sampler2D specular0;// grabs the specular map texture from main.cpp
uniform vec4 lightColor;    // gets the color variable from the main function
uniform vec3 lightPosition; // I think u get it by now cuh
uniform vec3 cameraPosition;

// as the name suggests, behaves like a spotlight.
// kinda like a flashlight in a videogame
vec4 spotLight()
{
    float outerCone = 0.90f;
    float innerCone = 0.95f;

    // detirmines strength of ambient lighting
    float ambient = 0.20f;

    // diffuse lighting
    vec3 lNormal = normalize(normal);
    vec3 lightDirection = normalize(lightPosition - currentPosition);
    float diffuse = max(dot(lNormal, lightDirection), 0.0f);

    // calculate specular lighting using our uniform variable
    // "cameraPosition" that we collect from our main.cpp function (glUniform3f(glGetUniformLocation))
    float specularLight = 0.50f;
    vec3 viewDirection = normalize(cameraPosition - currentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16.0f);
    float specular = specularAmount * specularLight;

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
    float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return (texture(diffuse0, texCoord) * (ambient + diffuse * intensity) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

// directional light is easy to think about as a sun,
// the source of light is (in theory) SO far that the light rays are practically
// parallel from one-another.
vec4 directionalLight()
{
    // detirmines strength of ambient lighting
    float ambient = 0.20f;

    // diffuse lighting
    vec3 lNormal = normalize(normal);
    vec3 lightDirection = normalize(vec3(1.0f, 5.0f, 0.0f));
    float diffuse = max(dot(lNormal, lightDirection), 0.0f);

    // calculate specular lighting using our uniform variable
    // "cameraPosition" that we collect from our main.cpp function (glUniform3f(glGetUniformLocation))
    float specularLight = 0.50f;
    vec3 viewDirection = normalize(cameraPosition - currentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16.0f);
    float specular = specularAmount * specularLight;

    return (texture(diffuse0, texCoord) * (ambient + diffuse) + texture(specular0, texCoord).r * specular) * lightColor;
}

// point lights are a type of light that emit light in EVERY direction,
// however falloff after distance you'd imagine a relation such as 1/d^2 right?
// however in computer graphics ppl like a way more complex version for more control (more visual style variety)
// more like y = 1/ax^2+bx+1 (quadratic ish formula where a and b typically sticks to around 0-1)
vec4 pointLight()
{
    vec3 lightVector = lightPosition - currentPosition;
    float dist = length(lightVector);
    float a = 1.0f;
    float b = 0.18f;
    float inten = 1.0f / (a * pow(dist, 2) + b * dist + 1.0f);

    // detirmines strength of ambient lighting
    float ambient = 0.20f;

    // diffuse lighting
    vec3 lNormal = normalize(normal);
    vec3 lightDirection = normalize(lightPosition - currentPosition);
    float diffuse = max(dot(lNormal, lightDirection), 0.0f);

    // calculate specular lighting using our uniform variable
    // "cameraPosition" that we collect from our main.cpp function (glUniform3f(glGetUniformLocation))
    float specularLight = 0.50f;
    vec3 viewDirection = normalize(cameraPosition - currentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8.0f);
    float specular = specularAmount * specularLight;

    return (texture(diffuse0, texCoord) * (ambient + diffuse * inten) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

void main()
{
    FragColor = pointLight();
};
