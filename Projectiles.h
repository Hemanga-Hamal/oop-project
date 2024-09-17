#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "raylib.h"

class Projectiles{
    protected:
        Vector2 proj_pos;
        Vector2 proj_speed;

        int proj_damage;
    public:
        // Constructor and Destructor
        Projectiles();
        virtual ~Projectiles();
        //Setters
        void virtual setProjPos(Vector2) = 0;
        void virtual setProjDamage(int) = 0;
        void virtual setProjSpeed(Vector2) = 0;

        //Getters
        Vector2 getProjSpeed();
        Vector2 getProjPos();
        int getProjDamage();
};

#endif