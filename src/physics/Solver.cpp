#include "Solver.h"
#include "constants.h"
#include "../state/Constraint.h"
#include "../state/World.h"

#include <vector>
#include <iostream>

Solver::Solver(World& w) : world(w) {}

void Solver::verletIntegrate(float dt){
    Vec2 velocity;

    for (auto& p : world.particles){
        velocity = p.pos - p.prevPos;
        p.prevPos = p.pos;
        
        p.pos += velocity + p.accel * dt * dt;
    }
}

void Solver::applyConstraints(){
    for (auto& c : world.constraints){
        c->apply();
    }
}

void Solver::solveCollisions(){
    for (std::size_t i {0}; i < world.particles.size(); ++i){
        Particle& p1 = world.particles[i];
        for (std::size_t j {i + 1}; j < world.particles.size(); ++j){
            Particle& p2 = world.particles[j];
            Vec2 collisionAxis = p1.pos - p2.pos;
            float dist = collisionAxis.magnitude();
            float combinedRadius = p1.radius + p2.radius;

            // Overlapping
            if (dist < combinedRadius){
                float correction = (combinedRadius - dist) * physics::FRICTION;
                Vec2 direction = dist > 0.0f
                    ? collisionAxis * (1.0f / dist)
                    : Vec2{1.0f, 0.0f};

                p1.pos += direction*(correction/2);
                p2.pos -= direction*(correction/2);
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
