#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "math/Vec2.h"

using std::vector;

constexpr float G { 9.8f };
constexpr int WIN_WIDTH { 1200 };
constexpr int WIN_HEIGHT { 800 };
constexpr float PHYSICS_STEP { 1.f/60 };

struct Particle {
    Vec2 pos;
    Vec2 prevPos;
    Vec2 accel;

    float radius;
};

void solve(vector<Particle>& parts, float dt=PHYSICS_STEP){
    Vec2 tmp{};
    Vec2 nextP{};

    for (auto& p : parts){
        tmp = p.pos;
        nextP = p.pos * 2 - p.prevPos + p.accel * dt * dt;

        p.pos = nextP;
        p.prevPos = tmp;

        if (p.pos.y > WIN_HEIGHT - p.radius){
            p.prevPos = p.pos + p.pos - p.prevPos;
        }
    }
}

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
    
    float dt{};
    while (!WindowShouldClose()) {

        dt = GetFrameTime();

        if (IsMouseButtonDown(0)){
            parts.push_back(Particle {
                Vec2{(float)GetMouseX(),
                (float)GetMouseY(),},
                Vec2{(float)GetMouseX(),
                (float)GetMouseY(),},

                Vec2{0,G},

                (float)(rand() % 10 + 10)
            });
        }

        // Solve
        for (int i = 0; i < 6; ++i){
            solve(parts, dt);
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