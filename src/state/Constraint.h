#pragma once

struct World;

class Constraint
{
public:
    virtual ~Constraint() = default;
    virtual void apply(World &) = 0;
};
