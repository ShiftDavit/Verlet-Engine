#pragma once

#include "../../state/Constraint.h"
#include "../../state/Particle.h"
#include <cstddef>
#include <vector>

class DistanceConstraint : public Constraint
{
public:
    DistanceConstraint(ParticleID first, ParticleID second, float distance);

    void apply(World &) override;

private:
    ParticleID p1ID, p2ID;
    float targetDistance;

    bool enabled;
};
