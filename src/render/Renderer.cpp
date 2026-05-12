#include "Renderer.h"
#include "raylib.h"

void drawParticle(Particle& p){
    DrawCircle(p.pos.x, p.pos.y, p.radius, RAYWHITE);
    DrawCircle(p.pos.x, p.pos.y, p.radius - 5, Color{30,30,30,255});
}