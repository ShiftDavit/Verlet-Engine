#pragma once

#include "Particle.h"
#include "Constraint.h"

#include <vector>
#include <memory>

struct World
{
    std::vector<Particle> particles;
    std::vector<Constraint *> constraints;

    void add(Particle &p) { particles.push_back(p); };
    void add(Constraint &c) { constraints.push_back(&c); };
};