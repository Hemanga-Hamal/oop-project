#ifndef ASTEROIDS_H
#define ASTEROIDS_H
#include "Enemy.h"

class Asteroids: protected Enemy{
    private:
        int asteroids_scale;
        int asteroids_damage;
    public:
        // Constructor
        Asteroids(int, int, float, float, float, float, float, int);

        // Setters
        void setAsteroidsDamage(int);
        void setAsteroidsScale(int);
        void setEnemyHealth(int);
        void setEnemySpeed(float, float);
        void setEnemyPos(Vector2);
        void setEnemyRotation(float);

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