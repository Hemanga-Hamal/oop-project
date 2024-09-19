#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Enemy.h"
#include "raylib.h"

class Asteroids : public Enemy {
private:
    // Asteroids stats
    int asterDmg;
    float asterScale;
    Vector2 Aster_Bounding;
    bool active; // Flag to check if asteroid is active

public:
    // Constructor
    Asteroids(Vector2 pos, Vector2 speed);

    // Getters
    int getAsteroidsDamage() const;
    float getAsteroidsScale() const;
    Vector2 getAsteroidsBounding() const;
    bool isActive() const; // Getter for active flag

    // Setters
    void setEnemyPos(Vector2 pos) override;
    void setEnemySpeed(Vector2 speed) override;
    void setEnemyHealth(int health) override;
    void setActive(bool state); // Setter for active flag

    // Collision logic
    bool checkColPlayer(Vector2 playerPos, Vector2 playerBounding, float pl_rot);

    // Movement
    void movement(float deltaTime) override;

    // Updating and Rendering
    void draw() override;
    void update(float deltaTime) override;

    // Set speed towards a target
    void setSpeedTowards(Vector2 target, float speed);

    // Reset asteroid position, speed, and size
    void reset(Vector2 newPos, Vector2 playerPos, float speed, float scale = -1.0f);
};

#endif
