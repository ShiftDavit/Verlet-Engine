#include "Application.h"
#include "raylib.h"
#include "../physics/constants.h"
#include "../render/Renderer.h"
#include "../physics/Solver.h"
#include "../state/SystemState.h"
#include "rlImGui.h"
#include "imgui.h"

#include <string>

using verlet::Application;

Application::Application()
{
    InitWindow(width, height, title);
}

void Application::OnRender() {}

void Application::Run()
{
    OnStart();
    rlImGuiSetup(true);
    SetTargetFPS(120);

    float eps{};
    float dt{};
    while (!WindowShouldClose())
    {
        dt = GetFrameTime();
        eps += dt;

        if (IsKeyPressed(KEY_F1))
        {
            debugMode = !debugMode;
        }

        OnUpdate(dt);

        // Physics step
        while (eps >= verlet::PHYSICS_STEP)
        {
            OnStep(verlet::PHYSICS_STEP);
            eps -= verlet::PHYSICS_STEP;
        }

        PostStep();

        // Render
        BeginDrawing();
        ClearBackground(Color{20, 20, 20, 20});

        rlImGuiBegin();
        OnRender();

        if (debugMode)
        {
            ImGui::Begin("Engine", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::Text(std::string{"FPS: " + std::to_string(1 / dt)}.c_str());
            ImGui::End();
        }
        rlImGuiEnd();

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
}
