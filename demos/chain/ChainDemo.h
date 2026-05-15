#pragma once

#include "../../engine/app/Application.h"
#include "../../engine/state/SystemState.h"
#include "../../engine/physics/Solver.h"

class ChainDemo : public verlet::Application
{
public:
    ChainDemo() {};

    void OnStart() override;
    void OnUpdate(float dt) override;
    void OnStep(float dt) override;
    void OnRender() override;

private:
    verlet::World world;
    verlet::Solver solver;

    int chainCount = 10;
    float spacing = 50.0f;
};