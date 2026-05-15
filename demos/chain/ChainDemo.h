#pragma once

#include "../../engine/app/Application.h"
#include "../../engine/state/SystemState.h"
#include "../../engine/physics/Solver.h"
#include "../../engine/math/Vec2.h"

struct MouseForce
{
    bool active = false;
    verlet::ParticleID target;
    float strength = 1000.0f;
};

class ChainDemo : public verlet::Application
{
public:
    ChainDemo() {};

    void OnStart() override;
    void OnUpdate(float dt) override;
    void OnStep(float dt) override;
    void PostStep() override;
    void OnRender() override;

private:
    verlet::World world;
    verlet::Solver solver;

    MouseForce mouseForce;

    int chainCount = 5;
    float spacing = 80.0f;
};