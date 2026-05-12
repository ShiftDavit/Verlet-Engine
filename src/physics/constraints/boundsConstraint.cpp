#include "BoundsConstraint.h"
#include "../constants.h"

BoundsConstraint::BoundsConstraint(std::vector<Particle>& particles)
    : particles(particles), left(0.0f), top(0.0f), right(0.0f), bottom(0.0f), enabled(false) {}

BoundsConstraint::BoundsConstraint(std::vector<Particle>& particles, float width, float height)
    : BoundsConstraint(particles, 0.0f, 0.0f, width, height) {}

BoundsConstraint::BoundsConstraint(
    std::vector<Particle>& particles,
    float left,
    float top,
    float right,
    float bottom
) : particles(particles), left(left), top(top), right(right), bottom(bottom), enabled(true) {}

void BoundsConstraint::apply(){
    if (!enabled){
        return;
    }

    for (auto& p : particles){
        const float minX = left + p.radius;
        const float maxX = right - p.radius;
        const float minY = top + p.radius;
        const float maxY = bottom - p.radius;

        const float velX = p.pos.x - p.prevPos.x;
        const float velY = p.pos.y - p.prevPos.y;

        if (p.pos.x < minX){
            p.pos.x = minX;
            p.prevPos.x = p.pos.x + velX * physics::FRICTION;
        } else if (p.pos.x > maxX){
            p.pos.x = maxX;
            p.prevPos.x = p.pos.x + velX * physics::FRICTION;
        }

        if (p.pos.y < minY){
            p.pos.y = minY;
            p.prevPos.y = p.pos.y + velY * physics::FRICTION;
        } else if (p.pos.y > maxY){
            p.pos.y = maxY;
            p.prevPos.y = p.pos.y + velY * physics::FRICTION;
        }
    }
}
