#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Enemy.h"
#include "raylib.h"

class Asteroids : public Enemy {
private:
    int asterDmg;
    int asterSize;
    float asterScale;
public:
    // Constructor
    Asteroids(Vector2 pos, Vector2 speed);

    // Getters
    int getAsteroidsDamage() const;
    float getAsteroidsScale() const;
    int getAsteroidsSize() const;

    // Setters
    void setEnemyPos(Vector2 pos) override;
    void setEnemySpeed(Vector2 speed) override;
    void setEnemyHealth(int health) override;

    // Movement
    void movement(float deltaTime) override;

    // Updating and Rendering
    void draw() override;
    void update(float deltaTime) override;
};

#endif
