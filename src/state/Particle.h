#pragma once

#include "../math/Vec2.h"

using ParticleID = int;

struct Particle
{
    Vec2 pos;
    Vec2 prevPos;
    Vec2 accel;

    float radius;
};