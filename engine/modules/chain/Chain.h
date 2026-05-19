#pragma once

#include "../../math/Vec2.h"
#include "../../state/SystemState.h"

#include <vector>

namespace verlet
{
    struct ChainConfig
    {
        Vec2 start = {0.0f, 0.0f};
        Vec2 direction = {0.0f, 1.0f};
        int linkCount = 2;
        float spacing = 50.0f;
        float particleRadius = 10.0f;
        Vec2 acceleration = {0.0f, G};
        bool pinFirst = true;
        bool pinLast = true;
    };

    class Chain
    {
    public:
        Chain() = default;
        Chain(World &world, const ChainConfig &config);

        void build(World &world, const ChainConfig &config);

        const std::vector<ParticleID> &particles() const;
        ParticleID particle(std::size_t index) const;
        std::size_t size() const;

    private:
        std::vector<ParticleID> particleIDs;
    };
}
