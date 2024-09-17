#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include "Projectiles.h"

Projectiles::Projectiles() {}

Vector2 Projectiles::getProjPos() {
    return proj_pos;
}

Vector2 Projectiles::getProjSpeed() {
    return proj_speed;
}

int Projectiles::getProjDamage() {
    return proj_damage;
}