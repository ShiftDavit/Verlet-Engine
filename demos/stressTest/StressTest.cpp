#include "StressTest.h"
#include "../../engine/physics/constraints/BoundsConstraint.h"
#include "raylib.h"

#include <iostream>

using namespace verlet;

constexpr int PARTICLE_RADIUS{10};
constexpr float KILL_DT_THRESHOLD{1.f / 60};

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

    if (elapsed > 1 && dt > KILL_DT_THRESHOLD)
    {
        killed = true;
    }

    if (!killed && elapsed - lastSpawnTime >= 1 / spawnRate)
    {
        lastSpawnTime = elapsed;
        // Spawn a particle
        world.add(Particle{
            {10, 10},
            {0, 10},

            {0, G},

            PARTICLE_RADIUS});
    }
}