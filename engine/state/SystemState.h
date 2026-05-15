#pragma once

#include "../math/Vec2.h"
#include "../physics/constants.h"
#include <vector>
#include <memory>

namespace verlet
{
    struct World;

    using ParticleID = int;

    struct Particle
    {
        verlet::Vec2 pos;
        verlet::Vec2 prevPos;
        verlet::Vec2 accel = Vec2{0, G};

        float radius;
        bool fixed = false;
    };

    class Constraint
    {
    public:
        virtual ~Constraint() = default;

        virtual void apply(World &world) = 0;
        virtual void draw(World &world) const {}; // optional
    };

    struct World
    {
        std::vector<Particle> particles;
        std::vector<std::unique_ptr<Constraint>> constraints; // Polymorphic so using pointers

        ParticleID add(const Particle &p)
        {
            particles.push_back(p);
            return particles.size() - 1;
        };
        void add(std::unique_ptr<Constraint> c) { constraints.push_back(std::move(c)); };
    };
}
