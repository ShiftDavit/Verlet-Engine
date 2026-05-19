#include "ChainDemo.h"
#include "../../engine/physics/constraints/BoundsConstraint.h"
#include "../../engine/render/Renderer.h"
#include "raylib.h"

using namespace verlet;

void ChainDemo::OnStart()
{
    ChainConfig config;
    config.start = {400.0f, 200.0f};
    config.linkCount = 5;
    config.spacing = 80.0f;
    config.particleRadius = 30.0f;

    chain.build(world, config);

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