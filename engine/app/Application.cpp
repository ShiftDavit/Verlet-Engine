#include "Application.h"
#include "raylib.h"
#include "../physics/constants.h"
#include "../render/Renderer.h"
#include "../physics/Solver.h"
#include "../state/SystemState.h"

using verlet::Application;

Application::Application()
{
    InitWindow(width, height, title);
}

void Application::OnRender() {}

void Application::Run()
{
    OnStart();

    float eps{};
    float dt{};
    while (!WindowShouldClose())
    {
        dt = GetFrameTime();
        eps += dt;

        OnUpdate(dt);

        // Physics step
        while (eps >= verlet::PHYSICS_STEP)
        {
            OnStep(verlet::PHYSICS_STEP);
            eps -= verlet::PHYSICS_STEP;
        }

        // Render
        BeginDrawing();
        ClearBackground(Color{20, 20, 20, 20});

        OnRender();

        EndDrawing();
    }

    CloseWindow();
}
