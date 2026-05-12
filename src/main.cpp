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
#include "physics/constraints/DistanceConstraint.h"
#include "physics/constraints/BoundsConstraint.h"

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

    Particle test1 {
        Vec2 {400, 200},
        Vec2 {400, 200},
        
        Vec2{0,physics::G},

        20
    };
    
    Particle test2 {
        Vec2 {500, 200},
        Vec2 {500, 200},
        
        Vec2{0,physics::G},

        20
    };
        
    vector<Particle> parts{};
    parts.push_back(test1);
    parts.push_back(test2);
    
    vector<Constraint*> constraints{};
    
    BoundsConstraint bCheck (WIN_WIDTH, WIN_HEIGHT);
    DistanceConstraint dCheck (0, 1, 80);
    World w {
        parts,
        constraints
    };

    constraints.push_back(&bCheck);
    constraints.push_back(&dCheck);
    
    Solver s(w);
    
    float eps{};
    float dt{};
    float particleSpawnTimer{};
    
    while (!WindowShouldClose()) {
        dt = GetFrameTime();
        eps += dt;
        particleSpawnTimer += dt;

        if (IsMouseButtonPressed(0) && particleSpawnTimer >= PARTICLE_SPAWN_INTERVAL){
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
