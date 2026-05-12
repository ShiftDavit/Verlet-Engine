#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "raylib.h"
#include "math/Vec2.h"
#include "physics/constants.h"
#include "physics/Solver.h"
#include "state/Particle.h"
#include "render/Renderer.h"

using std::vector, physics::PHYSICS_STEP;

constexpr int WIN_WIDTH { 1200 };
constexpr int WIN_HEIGHT { 800 };
constexpr float PARTICLE_SPAWN_INTERVAL { 0.05f };

void renderParticles(vector<Particle>& parts){
    for (auto& p : parts){
        drawParticle(p);
    }
}


int main(){
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "raylib test");
    //SetTargetFPS(60);

    vector<Particle> parts{};
    vector<Constraint*> constraints{};

    BoundsConstraint bCheck (parts, WIN_WIDTH, WIN_HEIGHT);

    constraints.push_back(&bCheck);

    World w {
        parts,
        constraints
    };

    Solver s(w);
    
    float eps{};
    float dt{};
    float particleSpawnTimer{};
    
    while (!WindowShouldClose()) {
        dt = GetFrameTime();
        eps += dt;
        particleSpawnTimer += dt;

        if (IsMouseButtonDown(0) && particleSpawnTimer >= PARTICLE_SPAWN_INTERVAL){
            particleSpawnTimer = 0.0f;

            Vec2 mousePos {(float)GetMouseX(),
                (float)GetMouseY()};

            Particle p {
                mousePos,
                mousePos - Vec2{5.f,0},

                Vec2{0,physics::G},

                (float)(rand() % 5 + 20)
            };
            w.particles.push_back(p);
        }

        // Solve
        if (eps >= PHYSICS_STEP){
            s.step(PHYSICS_STEP, 6);
            eps -= PHYSICS_STEP;
        }

        // Render
        BeginDrawing();
        ClearBackground(Color{20,20,20,20});

        renderParticles(w.particles);
        DrawFPS(10, 10);

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
