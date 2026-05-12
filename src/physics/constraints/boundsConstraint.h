#pragma once

#include <vector>

#include "../../state/Constraint.h"
#include "../../state/Particle.h"

class BoundsConstraint : public Constraint {
    public:
        BoundsConstraint(std::vector<Particle>& particles);
        BoundsConstraint(std::vector<Particle>& particles, float width, float height);
        BoundsConstraint(std::vector<Particle>& particles, float left, float top, float right, float bottom);

        void apply() override;

    private:
        std::vector<Particle>& particles;
        float left;
        float top;
        float right;
        float bottom;
        bool enabled;
};
