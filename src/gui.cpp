#include "gui.hpp"

void GUI::InitializeImGUI(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void GUI::NewFrameImGUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    DisplayCustomUI();
}

void GUI::RenderImGUI()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::CleanUpImGUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::DisplayCustomUI()
{
    ImGui::Begin("Point Light");
        ImGui::SliderInt("Rotation Angle", &lightAngle, 0.0f, 360.0f);
        ImGui::SliderFloat("Light Intensity", &lightIntensity, 0.0f, 25.0f);
        // ImGui::SliderFloat("Light Orbit Distance", &orbitDistance, 3.0f, 100.0f);
        // ImGui::ColorEdit3("Light Color", glm::value_ptr(lightColor));
        ImGui::Checkbox("Enable Auto-Rotate", &autoRotate);
        ImGui::Separator();
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();
}
