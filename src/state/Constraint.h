#pragma once

class Constraint {
    public:
        virtual ~Constraint() = default;
        virtual void apply() = 0;
};
