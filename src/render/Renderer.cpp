#include "Renderer.h"
#include "raylib.h"

#include "../state/Particle.h"
#include "../state/Constraint.h"
#include "../physics/constraints/DistanceConstraint.h"

void drawParticles(World &w)
{
    for (auto &p : w.particles)
    {
        DrawCircle(p.pos.x, p.pos.y, p.radius, RAYWHITE);
        DrawCircle(p.pos.x, p.pos.y, p.radius - 2, Color{30, 30, 30, 255});
    }
}

void drawConstraints(World &world)
{
    for (auto &c : world.constraints)
    {
        auto *dist =
            dynamic_cast<DistanceConstraint *>(c);

        if (dist)
        {
            Particle &a =
                world.particles[dist->p1ID];

            Particle &b =
                world.particles[dist->p2ID];

            DrawLineEx(Vector2{a.pos.x, a.pos.y}, Vector2{b.pos.x, b.pos.y}, 5.f, RAYWHITE);
        }
    }
}