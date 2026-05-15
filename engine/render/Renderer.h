#pragma once

#include "../state/SystemState.h"

namespace verlet
{
    void drawParticles(const World &);
    void drawConstraints(World &world);
}