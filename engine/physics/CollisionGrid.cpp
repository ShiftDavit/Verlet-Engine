#include "CollisionGrid.h"

#include <algorithm>
#include <cmath>

using verlet::CollisionGrid;

CollisionGrid::CollisionGrid(float cellSize)
    : cellSize(std::max(1.f, cellSize))
{
}

void CollisionGrid::add(verlet::ParticleID id, const verlet::Particle &p)
{
    grid[getCellIndex(p.pos)].push_back(id);
}

void CollisionGrid::getNearbyParticleIds(const verlet::Vec2 &pos, std::vector<verlet::ParticleID> &ids) const
{
    ids.clear();

    const int centerX = getCellCoordinate(pos.x);
    const int centerY = getCellCoordinate(pos.y);

    for (int y = centerY - 1; y <= centerY + 1; ++y)
    {
        for (int x = centerX - 1; x <= centerX + 1; ++x)
        {
            const auto cell = grid.find(getCellIndex(x, y));
            if (cell == grid.end())
            {
                continue;
            }

            ids.insert(ids.end(), cell->second.begin(), cell->second.end());
        }
    }
}

void CollisionGrid::clear()
{
    grid.clear();
}

int CollisionGrid::getCellIndex(const verlet::Vec2 &pos) const
{
    return getCellIndex(getCellCoordinate(pos.x), getCellCoordinate(pos.y));
}

int CollisionGrid::getCellIndex(int cellX, int cellY) const
{
    return (cellX * 73856093) ^ (cellY * 19349663);
}

int CollisionGrid::getCellCoordinate(float value) const
{
    return static_cast<int>(value / cellSize);
}
