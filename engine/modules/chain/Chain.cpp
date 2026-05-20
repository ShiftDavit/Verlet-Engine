#include "Chain.h"

#include "../../physics/constraints/DistanceConstraint.h"

#include <memory>
#include <vector>
#include <iostream>

using namespace verlet;

Chain::Chain(const std::vector<ChainEntry> &config) : entries(config) {}

void Chain::build(World &world)
{
    if (entries.size() < 2)
    {
        std::cout << "Chain is too short\n";
        return;
    }

    // register entries
    for (std::size_t i = 0; i + 1 < entries.size(); ++i)
    {
        world.add(std::make_unique<DistanceConstraint>(
            entries[i].particleId,
            entries[i + 1].particleId,
            entries[i + 1].distanceToPrevious));
    }
}

std::size_t Chain::size() const
{
    return entries.size();
}
