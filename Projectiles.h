#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "raylib.h"

class Projectiles{
    protected:
        Vector2 proj_pos;
        Vector2 proj_speed;
        int proj_damage;
    public:
        // Set/get position
        void virtual setProjPos(Vector2) = 0;
        Vector2 getProjPos();

        // Set/get speed
        void virtual setProjSpeed(Vector2) = 0;
        Vector2 getProjSpeed();

        // Set/get damage
        void virtual setProjDamage(int) = 0;
        int getProjDamage();

        // Default constructor
        Projectiles();

        // Destructor
        virtual ~Projectiles();
};

#endif