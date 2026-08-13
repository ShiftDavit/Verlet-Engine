# Verlet Physics Engine

A real-time 2D physics engine built in C++ using Verlet integration, featuring stable constraint solving, optimized collision detection, interactive grabbing, and rope/chain simulation.


https://github.com/user-attachments/assets/4e45b30c-b57d-47ee-8c88-c67f5275b5a5


---

## 🔧 Features

### Physics
- Position-based Verlet integration (no velocity state)
- Iterative constraint solver (4+ iterations/frame)
- Stable gravity and damping system
- Collision solving using spatial hashing

### Interaction
- Mouse-based particle grabbing
- Kinematic override using positional correction
- Smooth drag behavior without force instability

### Constraints
- Distance constraints (rope/chain simulation)
- Fixed anchor constraints
- Boundary collision constraints

---

## Optimization

Naive collision detection involves comparing every particle with every other particle in the system. This has an O(n^2) runtime complexity, meaning the number of collision checks will grow quadratically with the number of particles. With modern resources (my gaming laptop), this is perfectly fine for simulating ~300 bodies. But sometimes we want more...

A popular way to optimize collisions in a large group of objects is spatial hashing. The intuition is as follows: divide space into a grid and place objects in cells by hashing their coordinates to indices in a 2D matrix; assuming the cell size is large enough, for each object, only check for collisions in nearby cells. In the picture below, the dimensions of each cell are equivalent to the radius of all particles. This guarantees that a particle in a cell can at most collide with those in nearby cells. For my engine, I chose a cell size of 1.5 × (radius of the largest particle), as this resulted in the most stable collisions. 

<img width="1920" height="1080" alt="Spatial Hashing" src="https://github.com/user-attachments/assets/90265508-511c-4281-95f3-8c32c37d37ff" />

To test how effective this method is, I wrote a small stress-test demo that spawns particles until the average frame rate of the simulation drops below 60 FPS (started lagging).

### Naive Collisions
https://github.com/user-attachments/assets/2ca5a3f9-dec4-4f14-93b6-8bf920334fcd

### Spatial Hashing
https://github.com/user-attachments/assets/8ec6d36b-f2e5-4985-bf01-77f4e16aba87

Since every stress test resulted in a varying maximum number of particles that caused lag, I tested each approach over three trials and compared the averages. Spatial hashing roughly **quadrupled** the number of particles before the baseline frame rate was reached, clearly demonstrating the advantage.

<img width="597" height="150" alt="SpatialHashingStats" src="https://github.com/user-attachments/assets/abf6a204-a8e1-463c-a6ad-7eb0819e69d5" />

While in the worst case, the time complexity of this algorithm remains O(n^2) (if all particles were somehow in the same cell or nearby cells), it bumps down the average-case time complexity of collision checking to O(n)eliminating a significant portion of redundant checks. I came across this method in Matthias Müller's presentation ([Blazing Fast Neighbor Search
with Spatial Hashing](https://matthias-research.github.io/pages/tenMinutePhysics/11-hashing.pdf)).

---

## 🧠 Architecture

The engine is split into five main pieces: the application layer, world state, physics solver, renderer, and demos.

### Application Layer

`Application` owns the runtime loop and the active `World`. Each frame, it:

1. Initializes external systems (raylib and ImGui)
2. Advances the solver using a fixed timestep accumulator
3. Invokes hooks such as `OnUpdate()`, `OnStep()`, `PostStep()`, and `OnRender()`, allowing the user to hook into the loop at various points
4. Renders constraints, particles, and optional debug stats

Physics runs at a fixed `PHYSICS_STEP`, while rendering happens once per frame. This keeps the simulation more stable, especially at lower FPS, preventing high frame times from making the particles explode all over the place. Every step is also divided into substeps, which allows for more accurate collision and constraint solving, further stabilizing the simulation.

### World State

`World` is a lightweight container for simulation data:

- `particles` stores all active particles
- `constraints` stores polymorphic constraints such as bounds and distance constraints

Particles use Verlet-style state:

```cpp
struct Particle
{
    Vec2 pos;
    Vec2 prevPos;
    Vec2 accel;
    float radius;
    bool fixed;
};
```

Velocity is not stored directly. Instead, it is inferred from the difference between `pos` and `prevPos`.

### Physics Solver

The `Solver` mutates the `World` during each fixed physics step. Its pipeline is:

1. Apply constraints
2. Solve particle collisions
3. Integrate particle positions

Integration uses Verlet motion:

```cpp
velocity = p.pos - p.prevPos;
p.prevPos = p.pos;
p.pos += velocity + p.accel * dt * dt;
```

Collision detection is accelerated with a spatial hash grid. The solver rebuilds the grid from current particle positions, then checks only particles in nearby cells instead of comparing every pair globally.

### Constraints

Constraints are objects that apply rules to the world. Each constraint implements:

```cpp
virtual void apply(World &world) = 0;
virtual void draw(World &world) const {};
```

This allows constraints to affect physics and optionally render debug geometry. Current examples include boundary constraints and distance constraints for ropes/chains.

### Rendering and Debugging

Rendering is intentionally separate from simulation. The renderer reads the `World` and draws constraints and particles using Raylib. The debug panel uses ImGui to display frame time, FPS, physics accumulator state, particle count, and constraint count.

### Demos

Demos subclass `Application` and override hooks such as `OnStart`, `OnUpdate`, `OnStep`, and `OnRender`. This lets each demo define its own setup and behavior while reusing the same engine loop, world state, solver, renderer, and debug tools.

This separation allows stable simulation even under high constraint density.

---

## 🛠 Tech Stack
- C++
- Raylib
- ImGui
- Custom physics engine (no external physics libraries)

---

## 📚 What I Learned

This is one of my C++ projects, so I got to practice various foundational skills such as memory safety with smart pointers and multi-file modular projects. 
I also learned about how the backbones of modern real-time engines work and how they have evolved over the years.

---
## Build and Run
```bash
mkdir build
cd build

cmake ..
cmake --build .
./VerletEngine.exe
```
