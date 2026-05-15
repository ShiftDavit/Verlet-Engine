#include "BoundsConstraint.h"
#include "../constants.h"

using verlet::BoundsConstraint;

BoundsConstraint::BoundsConstraint(float width, float height)
    : BoundsConstraint(0.0f, 0.0f, width, height) {}

BoundsConstraint::BoundsConstraint(
    float left,
    float top,
    float right,
    float bottom) : left(left), top(top), right(right), bottom(bottom), enabled(true) {}

void BoundsConstraint::apply(World &w)
{
    if (!enabled)
    {
        return;
    }

    for (auto &p : w.particles)
    {
        if (p.fixed)
            continue;

        const float minX = left + p.radius;
        const float maxX = right - p.radius;
        const float minY = top + p.radius;
        const float maxY = bottom - p.radius;

        const float velX = p.pos.x - p.prevPos.x;
        const float velY = p.pos.y - p.prevPos.y;

        if (p.pos.x < minX)
        {
            p.pos.x = minX;
            p.prevPos.x = p.pos.x + velX * verlet::FRICTION;
        }
        else if (p.pos.x > maxX)
        {
            p.pos.x = maxX;
            p.prevPos.x = p.pos.x + velX * verlet::FRICTION;
        }

        if (p.pos.y < minY)
        {
            p.pos.y = minY;
            p.prevPos.y = p.pos.y + velY * verlet::FRICTION;
        }
        else if (p.pos.y > maxY)
        {
            p.pos.y = maxY;
            p.prevPos.y = p.pos.y + velY * verlet::FRICTION;
        }
    }
}
