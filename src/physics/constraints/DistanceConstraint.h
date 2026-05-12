#pragma once

#include "../../state/Constraint.h"
#include "../../state/Particle.h"
#include <cstddef>
#include <vector>

class DistanceConstraint : public Constraint {
    public:
        DistanceConstraint(std::size_t first, std::size_t second, float distance);

        void apply(World&) override;

    private:
        std::size_t a, b;
        float targetDistance;

        bool enabled;
};
