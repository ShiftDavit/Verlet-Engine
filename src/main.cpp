#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstdlib>

#include "raylib.h"
#include "math/Vec2.h"
#include "physics/constants.h"
#include "physics/Solver.h"
#include "state/World.h"
#include "state/Particle.h"
#include "render/Renderer.h"
#include "physics/constraints/DistanceConstraint.h"
#include "physics/constraints/BoundsConstraint.h"

using std::vector, physics::PHYSICS_STEP;

constexpr int WIN_WIDTH{1200};
constexpr int WIN_HEIGHT{800};
constexpr float PARTICLE_SPAWN_INTERVAL{0.01f};

void renderParticles(vector<Particle> &parts)
{
  for (auto &p : parts)
  {
    drawParticle(p);
  }
}

void drawBodyCount(World &w)
{
  const std::string bodyCount = "Particles: " + std::to_string(w.particles.size());
  DrawText(bodyCount.c_str(), 10, 40, 20, RAYWHITE);
}

int main()
{
  InitWindow(WIN_WIDTH, WIN_HEIGHT, "raylib test");
  // SetTargetFPS(60);

  World w{};
  Solver s(w);

  // Test particles
  Particle p1{
      Vec2{400, 500},
      Vec2{400, 500},

      Vec2{0, physics::G},

      20};

  Particle p2{
      Vec2{500, 500},
      Vec2{500, 500},

      Vec2{0, physics::G},

      20};

  w.add(p1);
  w.add(p2);

  // Test constraints
  DistanceConstraint distanceConstraint(0, 1, 80);
  BoundsConstraint boundsConstraint(WIN_WIDTH, WIN_HEIGHT);

  w.add(distanceConstraint);
  w.add(boundsConstraint);

  float eps{};
  float dt{};
  float particleSpawnTimer{};

  while (!WindowShouldClose())
  {
    dt = GetFrameTime();
    eps += dt;
    particleSpawnTimer += dt;

    if (IsMouseButtonDown(0) && particleSpawnTimer >= PARTICLE_SPAWN_INTERVAL)
    {
      particleSpawnTimer = 0.0f;

      Vec2 mousePos{(float)GetMouseX(),
                    (float)GetMouseY()};

      Particle p{
          mousePos,
          mousePos - Vec2{5.f, 0},

          Vec2{0, physics::G},

          (float)(rand() % 5 + 5)};
      w.add(p);
    }

    // Solve
    if (eps >= PHYSICS_STEP)
    {
      s.step(PHYSICS_STEP, 6);
      eps -= PHYSICS_STEP;
    }

    // Render
    BeginDrawing();
    ClearBackground(Color{20, 20, 20, 20});

    renderParticles(w.particles);

    // Debug
    DrawFPS(10, 10);
    drawBodyCount(w);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
