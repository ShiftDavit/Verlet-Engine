#pragma once
#include "../state/SystemState.h"

struct EngineDebugStats
{
    float frameDt{};
    float fixedPhysicsDt{};
    float physicsAccumulatorDt{};
    int physicsSteps{};
};

void DrawEngineStats(verlet::World &, const EngineDebugStats &stats);
