#pragma once

#include <vector>
#include "Particle.h"

class Solver {
    public:
        Solver(std::vector<Particle>&);
        void step(float dt);
    
    protected:
        std::vector<Particle>& particles;

        void verletIntegrate(float dt);
        void solveCollisions();
};