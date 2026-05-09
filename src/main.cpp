#include <iostream>
#include "raylib.h"

constexpr float G = 9.8f;
constexpr int WIN_WIDTH = 1200;
constexpr int WIN_HEIGHT = 800;


int main(){
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "raylib test");
    
    float v = 0.0f;
    float p = WIN_HEIGHT/2;

    while (!WindowShouldClose()) {
        BeginDrawing();

        v += G * 1.f/60;
        p += v * 1.f/60;

        ClearBackground(BLACK);
        DrawCircle(600, p, 10, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}