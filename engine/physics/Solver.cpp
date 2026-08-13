#include "Solver.h"
#include "CollisionGrid.h"
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
    float maxRadius = 1.f;
    for (const auto &p : world.particles)
    {
        maxRadius = std::max(maxRadius, p.radius);
    }

    CollisionGrid grid{maxRadius * 1.5f};
    for (std::size_t i{0}; i < world.particles.size(); ++i)
    {
        grid.add(static_cast<ParticleID>(i), world.particles[i]);
    }

    std::vector<ParticleID> nearbyParticleIds;
    for (std::size_t i{0}; i < world.particles.size(); ++i)
    {
        Particle &p1 = world.particles[i];
        grid.getNearbyParticleIds(p1.pos, nearbyParticleIds);

        for (ParticleID particleId : nearbyParticleIds)
        {
            if (particleId <= static_cast<ParticleID>(i))
            {
                continue;
            }

            Particle &p2 = world.particles[particleId];
            const Vec2 collisionAxis = p1.pos - p2.pos;
            const float dist = collisionAxis.magnitude();
            const float combinedRadius = p1.radius + p2.radius;

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
    applyConstraints(world);
    solveCollisions(world);
    verletIntegrate(world, dt);
}

void Solver::step(World &world, float dt, int subSteps)
{
    float subDt = dt / subSteps;

    for (int i{0}; i < subSteps; ++i)
    {
        step(world, subDt);
    }
}
