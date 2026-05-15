#include "DistanceConstraint.h"
#include "../../math/Vec2.h"
#include "../../state/SystemState.h"
#include "raylib.h"

#include <iostream>
#include <memory>

using verlet::DistanceConstraint;
using verlet::Particle;
using verlet::ParticleID;
using verlet::Vec2;
using verlet::World;

DistanceConstraint::DistanceConstraint(ParticleID first, ParticleID second, float distance)
    : p1ID(first), p2ID(second), targetDistance(distance), enabled(true) {};

void DistanceConstraint::apply(World &w)
{
    if (!enabled)
    {
        return;
    }

    Particle &p1{w.particles[p1ID]};
    Particle &p2{w.particles[p2ID]};

    if (targetDistance < p1.radius + p2.radius)
    {
        targetDistance = p1.radius + p2.radius;
    }
    Vec2 diff = p1.pos - p2.pos;
    float dist = diff.magnitude();

    if (dist < 1e-6f)
    {
        return;
    }

    float nudge = targetDistance - dist;
    Vec2 direction = diff.unit();

    if (!p1.fixed && !p2.fixed)
    {
        p1.pos += direction * (nudge * 0.5f);
        p2.pos -= direction * (nudge * 0.5f);
    }
    else if (!p1.fixed)
    {
        p1.pos += direction * nudge;
    }
    else if (!p2.fixed)
    {
        p2.pos -= direction * nudge;
    }
}

void DistanceConstraint::draw(World &w) const
{
    const auto &p1 = w.particles[p1ID];
    const auto &p2 = w.particles[p2ID];

    DrawLineEx(Vector2{p1.pos.x, p1.pos.y}, Vector2{p2.pos.x, p2.pos.y}, 10.f, RED);
}
