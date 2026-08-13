#pragma once

namespace verlet
{
    inline constexpr float G{5000.0f};
    inline constexpr float PHYSICS_STEP{1.f / 60};
    inline constexpr float FRICTION{.5f};
    inline constexpr int SUBSTEP_COUNT{4};
}
