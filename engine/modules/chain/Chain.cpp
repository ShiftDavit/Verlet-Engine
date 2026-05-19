#include "Chain.h"

#include "../../physics/constraints/DistanceConstraint.h"

#include <memory>

using namespace verlet;

Chain::Chain(World &world, const ChainConfig &config)
{
    build(world, config);
}

void Chain::build(World &world, const ChainConfig &config)
{
    particleIDs.clear();

    if (config.linkCount <= 0)
    {
        return;
    }

    Vec2 direction = config.direction;
    direction = direction.unit();
    if (direction.magnitude() < 1e-6f)
    {
        direction = {0.0f, 1.0f};
    }

    for (int i = 0; i < config.linkCount; ++i)
    {
        Particle particle;
        particle.pos = config.start + direction * (config.spacing * i);
        particle.prevPos = particle.pos;
        particle.accel = config.acceleration;
        particle.radius = config.particleRadius;
        particle.fixed = (config.pinFirst && i == 0) ||
                         (config.pinLast && i == config.linkCount - 1);

        particleIDs.push_back(world.add(particle));
    }

    for (std::size_t i = 0; i + 1 < particleIDs.size(); ++i)
    {
        world.add(std::make_unique<DistanceConstraint>(
            particleIDs[i],
            particleIDs[i + 1],
            config.spacing));
    }
}

const std::vector<ParticleID> &Chain::particles() const
{
    return particleIDs;
}

ParticleID Chain::particle(std::size_t index) const
{
    return particleIDs[index];
}

std::size_t Chain::size() const
{
    return particleIDs.size();
}
