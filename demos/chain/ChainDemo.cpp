#include "ChainDemo.h"
#include "../../engine/physics/constraints/BoundsConstraint.h"
#include "../../engine/render/Renderer.h"
#include "raylib.h"

#include <iostream>

using namespace verlet;

constexpr int PARTICLE_RADIUS{20};

void ChainDemo::OnStart()
{
    world.add(
        std::make_unique<BoundsConstraint>(
            width,
            height));
}

void ChainDemo::OnUpdate(float dt)
{
    if (IsKeyDown(KEY_D))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vec2 mouse{GetMousePosition()};
            drafts.push_back(mouse);
        }
    }

    if (IsKeyReleased(KEY_D))
    {
        if (drafts.size() > 1)
        {
            buildBuffer.push_back(
                {world.add(Particle{
                     drafts[0],
                     drafts[0],

                     {},

                     PARTICLE_RADIUS,
                     true}),
                 0});

            for (size_t i{1}; i < drafts.size(); ++i)
            {
                Vec2 &p{drafts[i]};
                Vec2 &prev{drafts[i - 1]};

                ChainEntry e{
                    world.add(Particle{
                        p,
                        p,

                        {},

                        PARTICLE_RADIUS}),

                    (p - prev).magnitude()};

                buildBuffer.push_back(e);
            }
        }

        Chain{buildBuffer}.build(world);

        buildBuffer.clear();
        drafts.clear();
    }
}

void ChainDemo::OnStep(float dt)

{
    for (auto &p : world.particles)
    {
        p.accel = {0, G};
    }

    Vec2 mouse{GetMousePosition()};

    if (IsMouseButtonDown(0) && !mouseForce.active)
    {
        float bestDist = 999999.0f;
        mouseForce.target = -1;

        for (int i = 0; i < world.particles.size(); i++)
        {
            auto &p = world.particles[i];

            float d = (p.pos - mouse).magnitude();

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

            Vec2 dir = mouse - p.pos;
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

    // draw draft chain
    if (drafts.size() > 0)
    {
        for (size_t i{0}; i + 1 < drafts.size(); ++i)
        {
            Vec2 &p{drafts[i]};
            Vec2 &next{drafts[i + 1]};

            DrawCircle(p.x, p.y, PARTICLE_RADIUS, Color{255, 255, 255, 50});
            DrawLineEx({p.x, p.y}, {next.x, next.y}, 5, Color{255, 255, 255, 50});
        }

        DrawCircle(drafts.back().x, drafts.back().y, PARTICLE_RADIUS, Color{255, 255, 255, 50});
    }

    drawConstraints(world);
    drawParticles(world);
}

void ChainDemo::PostStep()
{
}