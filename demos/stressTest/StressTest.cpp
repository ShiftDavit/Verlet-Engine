#include "StressTest.h"
#include "../../engine/physics/constraints/BoundsConstraint.h"
#include "../../engine/physics/constants.h"
#include "raylib.h"

#include <iostream>

using namespace verlet;

constexpr int PARTICLE_RADIUS{5};

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

    if (elapsed > 1 && dt > PHYSICS_STEP)
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