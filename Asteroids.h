#ifndef ASTEROIDS_H
#define ASTEROIDS_H
#include "Enemy.h"

class Asteroids: protected Enemy{
    private:
        int asteroids_scale;
        int asteroids_damage;
    public:
        // Constructor
        Asteroids(int, int);

        // Scaler
        void asteroidsStatsScale(int, int);

        // Setters
        void setAsteroidsDamage(int);
        void setAsteroidsScale(int);

        // Getters
        int getAsteroidsDamage();
        int getAsteroidsScale();

        // Updating and Rendering
        void draw();
        void update(float deltaTime);
};

#endif