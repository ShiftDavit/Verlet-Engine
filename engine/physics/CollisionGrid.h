#pragma once

#include <unordered_map>
#include <vector>

#include "../state/SystemState.h"

namespace verlet
{
    class CollisionGrid
    {
    public:
        explicit CollisionGrid(float cellSize = 1.f);

        void add(ParticleID id, const Particle &p);
        void getNearbyParticleIds(const Vec2 &pos, std::vector<ParticleID> &ids) const;
        void clear();

    private:
        int getCellIndex(const Vec2 &pos) const;
        int getCellIndex(int cellX, int cellY) const;
        int getCellCoordinate(float value) const;

        float cellSize;
        std::unordered_map<int, std::vector<ParticleID>> grid;
    };
}
