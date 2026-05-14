#pragma once

#include <vector>

#include "../../state/Constraint.h"
#include "../../state/Particle.h"
#include "../../state/World.h"

class BoundsConstraint : public Constraint {
    public:
        BoundsConstraint(float width, float height);
        BoundsConstraint(float left, float top, float right, float bottom);

        void apply(World&) override;

    private:
        float left;
        float top;
        float right;
        float bottom;
        bool enabled;
};
