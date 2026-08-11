#include "DebugPanel.h"
#include "../state/SystemState.h"
#include "rlImGui.h"
#include "imgui.h"
#include <string>

void DrawEngineStats(verlet::World &world, float drawDt, float physicsStepMs)
{
    ImGui::Begin("Engine Stats", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SeparatorText("Draw");
    ImGui::Text("FPS: %.2f", 1 / drawDt);
    ImGui::SeparatorText("Physics");
    ImGui::BeginGroup();
    ImGui::EndGroup();
    ImGui::Text("Step MS: %.2f", physicsStepMs);
    ImGui::SeparatorText("State");
    ImGui::Text("Particles: %d", world.particles.size());
    ImGui::Text("Constraints: %d", world.constraints.size());
    ImGui::End();
}