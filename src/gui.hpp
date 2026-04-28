#ifndef GUI_CLASS_H
#define GUI_CLASS_H

// #include <glm/glm.hpp>
// #include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class GUI
{
public:
    void InitializeImGUI(GLFWwindow* window);
    void NewFrameImGUI();
    void RenderImGUI();
    void CleanUpImGUI();

    // light parameter configuration
    int lightAngle = 0;
    float lightIntensity = 3;
    // todo :: implement orbit distance from origin.
    // float* orbitDistance;

    // light color configuration
    float
        red = 1.0f,
        green = 1.0f,
        blue = 1.0f;

    // detirmines if light should auto-rotate
    bool autoRotate = false;
private:
    void DisplayCustomUI();
};

#endif
