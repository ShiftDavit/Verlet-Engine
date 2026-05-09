#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"

using std::vector;

constexpr float G = 9.8f;
constexpr int WIN_WIDTH = 1200;
constexpr int WIN_HEIGHT = 800;

struct Particle {
    float x;
    float y;

    float vx;
    float vy;

    float radius;
};

void updateParticles(vector<Particle>& parts, float dt=1.f/60){
    for (auto& p : parts){
        p.vy += G * dt;

        p.x += p.vx * dt;
        p.y += p.vy * dt;
    }
}

void renderParticles(vector<Particle>& parts){
    for (auto& p : parts){
        DrawCircle(p.x, p.y, p.radius, WHITE);
    }
}

void showFps(float dt){
    std::string s = "FPS: " + std::to_string(1/dt);
    DrawText(s.c_str(), 10, 10, 20, WHITE);
}

int main(){
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "raylib test");
    SetTargetFPS(240);

    vector<Particle> parts {
        Particle {
            WIN_WIDTH/3,
            WIN_HEIGHT/2,

            10,
            -10,

            10
        },

        Particle {
            2 * WIN_WIDTH/3,
            WIN_HEIGHT/2,

            -5,
            -15,

            10
        },

        Particle {
            WIN_WIDTH/2,
            WIN_HEIGHT/2,

            0,
            0,

            10
        },
    };
    
    float dt;
    while (!WindowShouldClose()) {

        dt = GetFrameTime();
        // Solve
        updateParticles(parts, dt*5);
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