#ifndef GUI_CLASS_H
#define GUI_CLASS_H

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "light.hpp"

class GUI
{
public:
    void InitializeImGUI(GLFWwindow* window);
    void NewFrameImGUI(Light& light);
    void RenderImGUI();
    void CleanUpImGUI();

    // light parameter configuration
    int lightAngle = 0;
    // float lightIntensity = 3;

    // light color configuration
    float
        red = 1.0f,
        green = 1.0f,
        blue = 1.0f;

private:
    void DisplayCustomUI(Light& light);
};

#endif
