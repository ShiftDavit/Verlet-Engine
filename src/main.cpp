#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "math/Vec2.h"
#include "physics/constants.h"
#include "physics/Particle.h"
#include "physics/Solver.h"

using std::vector;

constexpr int WIN_WIDTH { 1200 };
constexpr int WIN_HEIGHT { 800 };

void renderParticles(vector<Particle>& parts){
    for (auto& p : parts){
        DrawCircle(p.pos.x, p.pos.y, p.radius, WHITE);
    }
}

void showFps(float dt){
    std::string s = "FPS: " + std::to_string(1/dt);
    DrawText(s.c_str(), 10, 10, 20, WHITE);
}

int main(){
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "raylib test");
    SetTargetFPS(60);

    vector<Particle> parts {
        
    };

    Solver s( parts );
    
    float dt{};
    while (!WindowShouldClose()) {

        dt = GetFrameTime();

        if (IsMouseButtonDown(0)){
            parts.push_back(Particle {
                Vec2{(float)GetMouseX(),
                (float)GetMouseY(),},
                Vec2{(float)GetMouseX(),
                (float)GetMouseY(),},

                Vec2{0,physics::G},

                (float)(rand() % 10 + 10)
            });
        }

        // Solve
        for (int i = 0; i < 6; ++i){
            s.step(dt);
        }
        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        showFps(dt);
        renderParticles(parts);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}