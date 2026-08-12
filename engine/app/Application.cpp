#include "Application.h"
#include "raylib.h"
#include "../physics/constants.h"
#include "../render/Renderer.h"
#include "../physics/Solver.h"
#include "../state/SystemState.h"
#include "rlImGui.h"
#include "imgui.h"
#include "../debug/DebugPanel.h"

#include <string>

using verlet::Application;

Application::Application()
{
    InitWindow(width, height, title);
}

void Application::Run()
{
    OnStart();
    rlImGuiSetup(true);
    SetTargetFPS(144);

    float eps{};
    float dt{};
    while (!WindowShouldClose())
    {
        dt = GetFrameTime();
        eps += dt;
        int physicsSteps{};

        if (IsKeyPressed(KEY_F1))
        {
            debugMode = !debugMode;
        }

        OnUpdate(dt);

        // Physics step
        while (eps >= verlet::PHYSICS_STEP)
        {
            OnStep(verlet::PHYSICS_STEP);
            solver.step(world, verlet::PHYSICS_STEP, verlet::SUBSTEP_COUNT);
            eps -= verlet::PHYSICS_STEP;
            ++physicsSteps;
        }

        PostStep();

        // Render
        BeginDrawing();
        ClearBackground(Color{10, 10, 10, 10});

        rlImGuiBegin();
        OnRender();
        drawConstraints(world);
        drawParticles(world);

        if (debugMode)
        {
            DrawEngineStats(
                world,
                EngineDebugStats{
                    dt,
                    verlet::PHYSICS_STEP,
                    eps,
                    physicsSteps});
        }

        rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
}
