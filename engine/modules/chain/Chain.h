#pragma once

#include "../../math/Vec2.h"
#include "../../state/SystemState.h"

#include <vector>

namespace verlet
{
    struct ChainEntry
    {
        ParticleID particleId;
        float distanceToPrevious;
    };

    class Chain
    {
    public:
        Chain() = default;
        Chain(const std::vector<ChainEntry> &config);

        void build(World &world);
        std::size_t size() const;

    private:
        std::vector<ChainEntry> entries;
    };
}
