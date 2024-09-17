#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include "Projectiles.h"

Projectiles::Projectiles():

Vector2 Projectiles::getProjPos() {
    return proj_pos;
}

 void virtual setProjPos(Vector2) = 0;
        Vector2 getProjPos();
        void virtual setProjSpeed(Vector2) = 0;
        Vector2 getProjSpeed();
        void virtual setProjDamage(int) = 0;
        int getProjDamage();
        Projectiles();
        virtual ~Projectiles();