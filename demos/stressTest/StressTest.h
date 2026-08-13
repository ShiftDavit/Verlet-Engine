#include "../../../engine/app/Application.h"

class StressTest : public verlet::Application
{
public:
    StressTest() { debugMode = true; };

    void OnStart() override;
    void OnUpdate(float dt) override;

private:
    int spawnRate{60};
    bool killed{false};
    float elapsed{};
    float lastSpawnTime{-1};
    float rollingDt{};
};