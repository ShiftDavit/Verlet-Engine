#include "ChainDemo.h"
#include "../../engine/physics/constraints/DistanceConstraint.h"
#include "../../engine/physics/constraints/BoundsConstraint.h"
#include "../../engine/render/Renderer.h"
#include "raylib.h"
#include <iostream>

using namespace verlet;

void ChainDemo::OnStart()
{

    // create particles
    for (int i = 0; i < chainCount; ++i)
    {
        Particle p;
        p.pos = {400, 200 + i * spacing};
        p.prevPos = p.pos;
        p.radius = 30;

        world.add(p);
    }

    world.particles[0].fixed = true;

    // create constraints
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

void ChainDemo::OnUpdate(float dt)
{
}

void ChainDemo::OnStep(float dt)

{
    for (auto &p : world.particles)
    {
        p.accel = {0, G};
    }

    Vector2 mouse = GetMousePosition();
    verlet::Vec2 m = {mouse.x, mouse.y};

    if (IsMouseButtonDown(0) && !mouseForce.active)
    {
        float bestDist = 999999.0f;
        mouseForce.target = -1;

        for (int i = 0; i < world.particles.size(); i++)
        {
            auto &p = world.particles[i];

            float d = (p.pos - m).magnitude();

            if (d < p.radius * 2 && d < bestDist)
            {
                bestDist = d;
                mouseForce.target = i;
                mouseForce.active = true;
            }
        }
    }

    // --- release ---
    if (IsMouseButtonUp(0))
    {
        mouseForce.active = false;
    }

    if (mouseForce.active && mouseForce.target >= 0)
    {
        auto &p = world.particles[mouseForce.target];

        if (!p.fixed)
        {
            auto &p = world.particles[mouseForce.target];

            Vec2 dir = m - p.pos;
            p.accel += dir * mouseForce.strength;
        }
    }

    solver.step(world, dt, 3);
}

void ChainDemo::OnRender()
{
    if (mouseForce.active)
    {
        auto &p = world.particles[mouseForce.target];
        DrawLineEx(GetMousePosition(), Vector2{p.pos.x, p.pos.y}, 2, RAYWHITE);
    }

    drawConstraints(world);
    drawParticles(world);
}

void ChainDemo::PostStep()
{
}