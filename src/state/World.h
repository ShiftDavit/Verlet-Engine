#pragma once

#include "Particle.h"
#include "Constraint.h"

#include <vector>
#include <memory>

struct World{
    std::vector<Particle>& particles;
    std::vector<Constraint*>& constraints;
};