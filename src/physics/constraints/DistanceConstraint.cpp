#include "DistanceConstraint.h"
#include "../../math/Vec2.h"
#include "../../state/World.h"

#include <iostream>
#include <memory>

DistanceConstraint::DistanceConstraint(ParticleID first, ParticleID second, float distance)
    : p1ID(first), p2ID(second), targetDistance(distance) {};

void DistanceConstraint::apply(World &w)
{
    Particle &p1{w.particles[p1ID]};
    Particle &p2{w.particles[p2ID]};

    if (targetDistance < p1.radius + p2.radius)
    {
        targetDistance = p1.radius + p2.radius;
    }
    Vec2 diff = p1.pos - p2.pos;
    float dist = diff.magnitude();
    float nudge = (targetDistance - dist) / 2;
    Vec2 direction = diff.unit();

    p1.pos += direction * nudge;
    p2.pos -= direction * nudge;
}
