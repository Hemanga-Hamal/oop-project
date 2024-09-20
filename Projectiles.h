#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "raylib.h"

class Projectiles{
    protected:
        //Stats
        Vector2 proj_pos;
        Vector2 proj_speed;
        int proj_damage;

    public:
        // Constructor and Destructor
        Projectiles(Vector2 pos, Vector2 speed, int damage);
        virtual ~Projectiles();

        //Setters
        void virtual setProjPos(Vector2) = 0;
        void virtual setProjDamage(int) = 0;
        void virtual setProjSpeed(Vector2) = 0;
        
        //Getters
        Vector2 getProjSpeed() const;
        Vector2 getProjPos() const;
        int getProjDamage() const;

        //Render
        virtual void draw() = 0;

        //Update
        virtual void update() = 0;
};

#endif