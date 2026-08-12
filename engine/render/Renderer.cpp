#include "Renderer.h"
#include "raylib.h"

#include "../state/SystemState.h"
#include "../physics/constraints/DistanceConstraint.h"

using namespace verlet;

void verlet::drawParticles(const World &w)
{
    for (auto &p : w.particles)
    {
        DrawCircle(p.pos.x, p.pos.y, p.radius, RAYWHITE);
    }
}

void verlet::drawConstraints(World &world)
{
    for (auto &c : world.constraints)
    {
        c->draw(world);
    }
}