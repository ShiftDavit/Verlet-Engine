#pragma once

#include <vector>

#include "../state/SystemState.h"

namespace verlet
{
    class Solver
    {
    public:
        Solver() {};

        void step(World &world, float dt);
        void step(World &world, float dt, int subSteps);

    protected:
        void verletIntegrate(World &world, float dt);
        void solveCollisions(World &world);
        void applyConstraints(World &world);
    };
}
