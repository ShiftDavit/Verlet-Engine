#include "ChainDemo.h"
#include "../../engine/physics/constraints/DistanceConstraint.h"
#include "../../engine/physics/constraints/BoundsConstraint.h"
#include "../../engine/render/Renderer.h"
#include <iostream>

using namespace verlet;

void ChainDemo::OnStart()
{
    for (int i = 0; i < chainCount; ++i)
    {
        Particle p;
        p.pos = {400 + i * spacing, 200 + i * 10.f};
        p.prevPos = p.pos;
        p.radius = 10;

        world.add(p);
    }

    world.particles[0].fixed = true;

    for (int i = 0; i < chainCount - 1; i++)
    {
        world.add(
            std::make_unique<DistanceConstraint>(
                i, i + 1, spacing));
    }

    world.add(
        std::make_unique<BoundsConstraint>(
            width,
            height));
}

void ChainDemo::OnStep(float dt)
{
    solver.step(world, dt, 8);
}

void ChainDemo::OnRender()
{
    drawConstraints(world);
    drawParticles(world);
}

void ChainDemo::OnUpdate(float dt)
{
}