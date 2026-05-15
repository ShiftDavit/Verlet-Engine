# ⚡ Verlet Physics Engine

![demo gif](demo.gif)

A real-time 2D physics engine built in C++ using Verlet integration, featuring stable constraint solving, interactive grabbing, and rope/chain simulation.

---

## 🔧 Features

### Physics
- Position-based Verlet integration (no velocity state)
- Iterative constraint solver (8+ iterations/frame)
- Stable gravity and damping system

### Interaction
- Mouse-based particle grabbing
- Kinematic override using positional correction
- Smooth drag behavior without force instability

### Constraints
- Distance constraints (rope/chain simulation)
- Fixed anchor constraints
- Boundary collision constraints

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
