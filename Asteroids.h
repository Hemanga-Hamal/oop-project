#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Enemy.h"
#include "Player.h"
#include "raylib.h"

class Asteroids : public Enemy {
private:
    // Asteroids stats
    int asterDmg;
    float asterScale;
    Vector2 Aster_Bounding;
    bool active;

public:
    // Constructor
    Asteroids(Vector2 pos, Vector2 speed);

    // Spawn at edges
    void spawnAtEdge();

    // Getters
    int getAsteroidsDamage() const;
    float getAsteroidsScale() const;
    Vector2 getAsteroidsBounding() const;
    bool isActive() const;

    // Setters
    void setEnemyPos(Vector2 pos) override;
    void setEnemySpeed(Vector2 speed) override;
    void setEnemyHealth(int health) override;
    void setActive(bool state);

    // Collision logic
    bool checkColPlayer(Vector2 playerPos, Vector2 playerBounding, float pl_rot);

    // Movement
    void movement(float deltaTime) override;

    // Updating and Rendering
    void draw() override;
    void update(float deltaTime) override;

    // Set speed towards a target
    void setSpeedTowards(Vector2 target, float speed);

    // Spawns a new asteroid after an existing one is destroyed
    void spawnNewAsteroid(Vector2 playerPos, float baseSpeed);

    // Handle collision with player and perform relevant actions
    bool handlePlayerCollision(Vector2 playerPos, Vector2 playerBounding, float pl_rot, Player& player);

    // Update asteroid, manage its state, and respawn if necessary
    void update(float deltaTime, Vector2 playerPos, float baseSpeed, Player& player);

    /*
    // Reset asteroid position, speed, and size
    void reset(Vector2 newPos, Vector2 playerPos, float speed, float scale = -1.0f);
    */
};

#endif
