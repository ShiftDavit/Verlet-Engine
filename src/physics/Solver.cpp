#include "Solver.h"
#include "constants.h"
#include <vector>
#include <iostream>
#include "constraints/Constraint.h"

Solver::Solver(std::vector<Particle>& p) : particles(p) {}

void Solver::addConstraint(Constraint& constraint){
    constraints.push_back(&constraint);
};

void Solver::addParticle(const Particle& particle){
    particles.push_back(particle);
};

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

void Solver::applyConstraints(){
    for (auto& c : constraints){
        c->apply();
    }
}

void Solver::step(float dt=physics::PHYSICS_STEP) {

    verletIntegrate(dt);
    applyConstraints();

}
