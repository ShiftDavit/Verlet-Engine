#pragma once

#include <vector>
#include "../Particle.h"

class Constraint {
    public:
        virtual ~Constraint() = default;
        virtual void apply() = 0;
};
