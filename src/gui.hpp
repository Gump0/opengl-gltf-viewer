#ifndef GUI_CLASS_H
#define GUI_CLASS_H

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
};

#endif
