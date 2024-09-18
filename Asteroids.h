#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Enemy.h"
#include "raylib.h"

class Asteroids: protected Enemy{
    private:
        int asteroids_scale;
        int asteroids_damage;
    public:
        // Constructor
        Asteroids(int scale, int size, Vector2 pos, Vector2 speed, int);

        // Setters
        void setEnemyPos(Vector2);
        void setEnemySpeed(Vector2);
        void setAsteroidsDamage(int);
        void setAsteroidsScale(int);
        void setEnemyHealth(int);

        // Getters
        int getAsteroidsDamage();
        int getAsteroidsScale();

        // Movement
        void movement(float, float);

        // Updating and Rendering
        void draw();
        void update(float deltaTime);
};

#endif