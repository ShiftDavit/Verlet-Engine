#include "StressTest.h"
#include "../../engine/physics/constraints/BoundsConstraint.h"
#include "../../engine/physics/constants.h"
#include "raylib.h"

#include <iostream>

using namespace verlet;

constexpr int PARTICLE_RADIUS{5};
constexpr float ROLLING_AVERAGE_WEIGHT{0.5};

void StressTest::OnStart()
{
    world.add(
        std::make_unique<BoundsConstraint>(
            width,
            height));
}

void StressTest::OnUpdate(float dt)
{
    elapsed += dt;

    if (elapsed < 3)
        return;

    if (rollingDt == 0)
    {
        rollingDt = dt;
    }

    rollingDt = rollingDt * (1.f - ROLLING_AVERAGE_WEIGHT) + dt * ROLLING_AVERAGE_WEIGHT;

    if (elapsed > 1 && rollingDt > PHYSICS_STEP)
    {
        killed = true;
    }

    if (!killed && elapsed - lastSpawnTime >= 1.f / (spawnRate > 0 ? spawnRate : 1))
    {
        lastSpawnTime = elapsed;
        // Spawn a particle
        world.add(Particle{
            {PARTICLE_RADIUS, PARTICLE_RADIUS},
            {PARTICLE_RADIUS * .3, PARTICLE_RADIUS},

            {0, G},

            PARTICLE_RADIUS});
    }
}
