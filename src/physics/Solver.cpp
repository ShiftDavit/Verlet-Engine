#include "Solver.h"
#include "constants.h"
#include <vector>
#include <iostream>

Solver::Solver(std::vector<Particle>& p) : particles(p){}

void Solver::verletIntegrate(float dt){
    Vec2 tmp{};
    Vec2 nextP{};

    for (auto& p : particles){
        tmp = p.pos;
        nextP = p.pos * 2 - p.prevPos + p.accel * dt * dt;

        p.pos = nextP;
        p.prevPos = tmp;
    }
}

void Solver::step(float dt=physics::PHYSICS_STEP) {
    verletIntegrate(dt);
}