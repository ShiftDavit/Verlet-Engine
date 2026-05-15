#pragma once

#include "../physics/Solver.h"
#include "../state/SystemState.h"

namespace verlet
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        virtual void OnStart() {};
        virtual void OnUpdate(float dt) {};

        virtual void OnStep(float dt) {};
        virtual void PostStep() {};

        virtual void OnRender();

        void Run();

    protected:
        int width = 1280;
        int height = 720;
        const char *title = "Verlet Engine";
    };
}