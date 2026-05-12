#include "DistanceConstraint.h"
#include "../../math/Vec2.h"
#include "../../state/World.h"

#include <iostream>
#include <memory>

DistanceConstraint::DistanceConstraint(std::size_t first, std::size_t second, float distance)
    : a(first), b(second), targetDistance(distance) {};

void DistanceConstraint::apply(World& w){
    Particle& p1 = w.particles[a];
    Particle& p2 = w.particles[b];

    if (targetDistance < p1.radius + p2.radius){
        targetDistance = p1.radius + p2.radius;
    } 
    Vec2 diff = p1.pos - p2.pos;
    float dist = diff.magnitude();
    float nudge = (targetDistance - dist)/2;
    Vec2 direction = diff.unit();

    p1.pos += direction * nudge;
    p2.pos -= direction * nudge;
}
