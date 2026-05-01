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

void GUI::NewFrameImGUI(Light& light)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    DisplayCustomUI(light);
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

void GUI::DisplayCustomUI(Light& light)
{
    ImGui::Begin("Point Light");
        ImGui::ColorEdit4("Light Color", glm::value_ptr(light.lightColor));
        ImGui::DragFloat3("Light Position", glm::value_ptr(light.lightPosition), 0.1f);
        // ImGui::SliderFloat("Light Intensity", &lightIntensity, 0.0f, 25.0f);
        ImGui::Separator();
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();
}
