#include "ZydecoCommon.hpp"
#include "GLRenderObject.hpp"
#include "GLRenderObjectImGui.hpp"
#include "Mandelbrot.hpp"


GLRenderObjectImGui::GLRenderObjectImGui(MandelbrotSettings *p_settings):
    GLRenderObject::GLRenderObject("", 10), m_pSettings(p_settings)
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
    static bool show_settings_window = true;
    if (ImGui::BeginMainMenuBar())
    {
        ImGui::MenuItem("Zydeco", nullptr, &show_demo_window, false);
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("ImGui Demo", nullptr, &show_demo_window, true);
            ImGui::MenuItem("About", nullptr, &show_about_window, true);
            ImGui::EndMenu();
        }
        ImGui::MenuItem("Fractal Settings", nullptr, &show_settings_window, true);
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
    if (show_settings_window)
    {
        ImGui::SetNextWindowSize({0, 0});
        if (ImGui::Begin("Fractal Settings", &show_settings_window, 0))
        {
            ImGui::PushItemWidth(150);
            if (ImGui::DragFloat("Re[z]", &m_pSettings->param_z, 0.0025, -6, 6)) { m_pSettings->restart = true; }
            //if (ImGui::SliderInt("Max Iteration Count\n(Unscaled)", &m_pSettings->iteration_count, 0, 5000)) { m_pSettings->restart = true; }
            if (ImGui::SliderInt("Iteration Step", &m_pSettings->iteration_step, 50, 1000)) { m_pSettings->restart = true; }
            if (ImGui::DragFloat("Discard Threshold", &m_pSettings->discard_threshold, 0.01, 0.01, 16.)) { m_pSettings->restart = true; }
            ImGui::DragFloat("Brightness", &m_pSettings->brightness, 0.1, 0.1, 100.0);
            ImGui::PopItemWidth();
            if (ImGui::Checkbox("Enable Interlacing", (bool*)(&m_pSettings->do_interlacing))) { m_pSettings->restart = true; }
            ImGui::Text("Zoom: %.6Le\nX: %.6Le\nY: %.6Le\nIteration %i\nFirst Interlace %i\nInterlace Layer %i\nIteration Count (Scaled): %i",
                m_pSettings->zoom,
                m_pSettings->pos_x,
                m_pSettings->pos_y,
                m_pSettings->current_iteration,
                m_pSettings->first_interlace,
                m_pSettings->interlace_layer,
                m_pSettings->adjusted_iteration_step);
            if (ImGui::Button("Reset"))
            {
                m_pSettings->zoom = 2.0;
                m_pSettings->pos_x = 0.0;
                m_pSettings->pos_y = 0.0;

                m_pSettings->first_interlace = 1;
                m_pSettings->interlace_layer = 0;
                m_pSettings->param_z = 0.0;
                m_pSettings->brightness = 1.0;
                m_pSettings->iteration_count = 100;
                m_pSettings->iteration_step = 50;
                m_pSettings->adjusted_iteration_step = 50;
                m_pSettings->current_iteration = 0;
                m_pSettings->discard_threshold = 4.;
            }
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
