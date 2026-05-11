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
    Vec2 velocity;

    for (auto& p : particles){
        velocity = p.pos - p.prevPos;
        p.prevPos = p.pos;
        
        p.pos += velocity + p.accel * dt * dt;
    }
}

void Solver::applyConstraints(){
    for (auto& c : constraints){
        c->apply();
    }
}

void Solver::solveCollisions(){
    for (int i {0}; i < particles.size(); ++i){
        for (int j {0}; j < particles.size(); ++j){
            if (i==j) continue;

            Vec2 collisionAxis = particles[i].pos - particles[j].pos;
            float dist = collisionAxis.magnitude();
            float combinedRadius = particles[i].radius + particles[j].radius;

            // Overlapping
            if (dist < combinedRadius){
                float correction = (combinedRadius - dist) * physics::FRICTION;
                Vec2 direction = collisionAxis.unit();

                particles[i].pos += direction*(correction/2);
                particles[j].pos -= direction*(correction/2);
            }
        }
    }
}

void Solver::step(float dt) {
    verletIntegrate(dt);
    applyConstraints();
    solveCollisions();
}

void Solver::step(float dt, int subSteps){
    float subDt = dt/subSteps;

    for (int i { 0 }; i < subSteps; ++i){
        step(subDt);
    }
}