#include "Solver.h"
#include "constants.h"
#include "../state/SystemState.h"

#include <vector>
#include <iostream>

using verlet::Solver;

void Solver::verletIntegrate(World &world, float dt)
{
    Vec2 velocity;

    for (auto &p : world.particles)
    {
        std::cout << p.fixed << "\n";
        if (p.fixed)
            continue;
        velocity = p.pos - p.prevPos;
        p.prevPos = p.pos;

        p.pos += velocity + p.accel * dt * dt;
    }
}

void Solver::applyConstraints(World &world)
{
    for (auto &c : world.constraints)
    {
        c->apply(world);
    }
}

void Solver::solveCollisions(World &world)
{
    for (std::size_t i{0}; i < world.particles.size(); ++i)
    {
        Particle &p1 = world.particles[i];
        for (std::size_t j{i + 1}; j < world.particles.size(); ++j)
        {
            Particle &p2 = world.particles[j];
            Vec2 collisionAxis = p1.pos - p2.pos;
            float dist = collisionAxis.magnitude();
            float combinedRadius = p1.radius + p2.radius;

            // Overlapping
            if (dist < combinedRadius)
            {
                float correction = (combinedRadius - dist) * FRICTION;
                Vec2 direction = collisionAxis.unit();

                if (!p1.fixed)
                    p1.pos += direction * (correction / 2);
                if (!p2.fixed)
                    p2.pos -= direction * (correction / 2);
            }
        }
    }
}

void Solver::step(World &world, float dt)
{
    verletIntegrate(world, dt);
    applyConstraints(world);
    solveCollisions(world);
}

void Solver::step(World &world, float dt, int subSteps)
{
    float subDt = dt / subSteps;

    for (int i{0}; i < subSteps; ++i)
    {
        step(world, subDt);
    }
}
