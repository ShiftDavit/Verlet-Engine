#include "DebugPanel.h"
#include "../state/SystemState.h"
#include "rlImGui.h"
#include "imgui.h"

void DrawEngineStats(verlet::World &world, const EngineDebugStats &stats)
{
    static float lastDt = 0;
    float avgDt = (stats.frameDt + lastDt) / 2;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::Begin("Engine Stats", nullptr, ImGuiWindowFlags_Modal);
    ImGui::SeparatorText("Draw");
    ImGui::Text("Frame Time: %.2f ms", avgDt * 1000.f);
    ImGui::Text("FPS: %d", (int)(1 / avgDt));

    ImGui::SeparatorText("Physics");
    ImGui::Text("Fixed Step: %.2f ms", stats.fixedPhysicsDt * 1000.f);
    ImGui::Text("Accumulator: %.2f ms", stats.physicsAccumulatorDt * 1000.f);
    ImGui::Text("Steps This Frame: %d", stats.physicsSteps);

    ImGui::SeparatorText("State");
    ImGui::Text("Particles: %d", world.particles.size());
    ImGui::Text("Constraints: %d", world.constraints.size());
    ImGui::End();

    lastDt = stats.frameDt;
}
