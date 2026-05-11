#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "math/Vec2.h"
#include "physics/constants.h"
#include "physics/Particle.h"
#include "physics/Solver.h"

using std::vector, physics::PHYSICS_STEP;

constexpr int WIN_WIDTH { 1200 };
constexpr int WIN_HEIGHT { 800 };

void renderParticles(vector<Particle>& parts){
    for (auto& p : parts){
        DrawCircle(p.pos.x, p.pos.y, p.radius, WHITE);
    }
}


int main(){
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "raylib test");
    //SetTargetFPS(60);

    vector<Particle> parts{};
    BoundsConstraint bCheck (parts, WIN_WIDTH, WIN_HEIGHT);

    Solver s(parts);
    s.addConstraint(bCheck);
    
    float eps{};
    float dt{};
    
    while (!WindowShouldClose()) {
        dt = GetFrameTime();
        eps += dt;

        if (IsMouseButtonPressed(0)){

            Vec2 mousePos {(float)GetMouseX(),
                (float)GetMouseY()};

            Particle p {
                mousePos,
                mousePos - Vec2{3.f,0},

                Vec2{0,physics::G},

                (float)(rand() % 5 + 10)
            };
            s.addParticle(p);
        }

        // Solve
        if (eps >= PHYSICS_STEP){
            s.step(PHYSICS_STEP);
            eps -= PHYSICS_STEP;
        }

        // Render
        BeginDrawing();
        ClearBackground(Color{20,20,20,20});

        DrawFPS(10, 10);
        renderParticles(parts);

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
