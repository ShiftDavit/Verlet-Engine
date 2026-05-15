#pragma once

#include "../../state/SystemState.h"
#include <cstddef>
#include <vector>

namespace verlet
{
    class DistanceConstraint : public Constraint
    {
    public:
        DistanceConstraint(ParticleID first, ParticleID second, float distance);

        void apply(World &) override;
        void draw(World &) const override;

        ParticleID p1ID, p2ID;
        float targetDistance;

        bool enabled;
    };
}
