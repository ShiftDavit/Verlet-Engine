#pragma once

#include <vector>
#include "Particle.h"
#include "constraints/boundsConstraint.h"
#include "constraints/Constraint.h"

class Solver {
    public:
        Solver(std::vector<Particle>&);

        void step(float dt);
        void step(float dt, int subSteps);
        void addConstraint(Constraint& constraint);
        void addParticle(const Particle& particle);

    protected:
        std::vector<Particle>& particles;
        std::vector<Constraint*> constraints;

        void verletIntegrate(float dt);
        void solveCollisions();
        void applyConstraints();
};
