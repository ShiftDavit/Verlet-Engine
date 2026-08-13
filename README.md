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

While in the worst case, the time complexity of this algorithm remains O(n^2) (if all particles were somehow in the same cell or nearby cells), it bumps down the average-case time complexity of collision checking to O(n)eliminating a significant portion of redundant checks. I came across this method in Matthias Müller's paper (https://matthias-research.github.io/pages/tenMinutePhysics/11-hashing.pdf).

---

## 🧠 Architecture

The engine runs in 3 stages per frame:
1. Verlet integration step
2. Constraint solving (iterative relaxation)
3. Rendering

This separation allows stable simulation even under high constraint density.

---

## 🛠 Tech Stack
- C++
- Raylib
- ImGui
- Custom physics engine (no external physics libraries)

---

## 📚 What I Learned

- Why Verlet integration is more stable than velocity-based systems
- How constraint iteration affects stability vs performance
- Debugging long-term numerical drift in physics simulations

---
## Build and Run
```bash
mkdir build
cd build

cmake ..
cmake --build .
./VerletEngine.exe
```
