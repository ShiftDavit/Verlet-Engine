#pragma once

#include <vector>

#include "../state/Particle.h"
#include "../state/Constraint.h"
#include "../state/World.h"
#include "constraints/boundsConstraint.h"

class Solver {
    public:
        Solver(World&);

        void step(float dt);
        void step(float dt, int subSteps);

    protected:
        World world;

        void verletIntegrate(float dt);
        void solveCollisions();
        void applyConstraints();
};
