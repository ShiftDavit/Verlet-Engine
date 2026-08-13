#include "DebugPanel.h"
#include "../state/SystemState.h"
#include "rlImGui.h"
#include "imgui.h"

constexpr int UPDATE_RATE{10}; // per second

void DrawEngineStats(verlet::World &world, const EngineDebugStats &stats)
{
    static float elapsed{};
    static float lastUpdated{};
    static EngineDebugStats lastObserved{};

    if (elapsed - lastUpdated > 1.f / UPDATE_RATE)
    {
        lastUpdated = elapsed;
        lastObserved = stats;
    }
    elapsed += stats.frameDt;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::Begin("Engine Stats", nullptr, ImGuiWindowFlags_Modal);
    ImGui::SeparatorText("Draw");
    ImGui::Text("Frame Time: %.2f ms", lastObserved.frameDt * 1000.f);
    ImGui::Text("FPS: %d", (int)(1 / lastObserved.frameDt));

    ImGui::SeparatorText("Physics");
    ImGui::Text("Fixed Step: %.2f ms", lastObserved.fixedPhysicsDt * 1000.f);
    ImGui::Text("Accumulator: %.2f ms", lastObserved.physicsAccumulatorDt * 1000.f);
    ImGui::Text("Steps This Frame: %d", lastObserved.physicsSteps);

    ImGui::SeparatorText("State");
    ImGui::Text("Particles: %d", world.particles.size());
    ImGui::Text("Constraints: %d", world.constraints.size());
    ImGui::End();
}
