#include "ZydecoCommon.hpp"
#include "GLRenderObject.hpp"
#include "GLRenderObjectImGui.hpp"


GLRenderObjectImGui::GLRenderObjectImGui():
    GLRenderObject::GLRenderObject("", 10)
{
    m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("/usr/share/fonts/FiraSans-Regular.ttf", 14);
    ImGui_ImplOpenGL3_CreateFontsTexture();
}

void GLRenderObjectImGui::Render()
{
    if (!m_renderEnabled) { return; }

    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();

    ImGui::NewFrame();

    auto mods  = io.KeyMods;
    auto ctrl  = io.KeyCtrl;
    auto alt   = io.KeyAlt;
    auto shift = io.KeyShift;

    ImGui::StyleColorsClassic();
    ImGui::PushFont(m_font);

    static bool show_demo_window = false;
    static bool show_about_window = false;
    if (ImGui::BeginMainMenuBar())
    {
        ImGui::MenuItem("Zydeco", nullptr, &show_demo_window, false);
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("ImGui Demo", nullptr, &show_demo_window, true);
            ImGui::MenuItem("About", nullptr, &show_about_window, true);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode, nullptr);

    if (show_demo_window) { ImGui::ShowDemoWindow(&show_demo_window); }
    if (show_about_window)
    {
        ImGui::SetNextWindowSize({350, 120});
        if (ImGui::Begin("About", &show_about_window, ImGuiWindowFlags_Modal | ImGuiWindowFlags_NoCollapse
                                                    | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize))
        {
            ImGui::Text("Zydeco (c) 2023 Joshua Stockin");
            ImGui::Text("<https://joshstock.in> <josh@joshstock.in>");
            ImGui::Separator();
            ImGui::TextWrapped("Zydeco is an experimental project in C++, graphics programming with OpenGL, procedural generation, and world simulation.");
            ImGui::End();
        }
    }

    ImGui::PopFont();

    io.KeyMods  = mods;
    io.KeyCtrl  = ctrl;
    io.KeyAlt   = alt;
    io.KeyShift = shift;

    ImGui::Render();
    ImGui::UpdatePlatformWindows();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
