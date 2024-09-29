#pragma once
#include "Enemy.h"
#include "Player.h"
#include "raylib.h"
#include <memory>

class Asteroids : public Enemy {
private:
    float asterScale;
    int asterDmg;
    Vector2 Aster_Bounding;
    bool active;

public:
    // Constructor
    Asteroids(Vector2 pos, Vector2 speed);

    // Setters
    void setEnemyPos(Vector2 pos) override;
    void setEnemySpeed(Vector2 speed) override;
    void setEnemyHealth(int health) override;
    void setActive(bool state);

    // Getters
    int getAsteroidsDamage() const;
    float getAsteroidsScale() const;
    Vector2 getAsteroidsBounding() const;
    bool isActive() const;

    // Check and break apart
    int checkSize();
    void breakApart(std::vector<std::unique_ptr<Asteroids>>& asteroidsList);

    // Take Damage
    void takeDamage(int damage);
    
    // Movement
    void movement(float deltaTime) override;

    // Collision logic  
    bool checkColPlayer(Vector2 playerPos, Vector2 playerBounding, float pl_rot);
    bool handlePlayerCollision(Vector2 playerPos, Vector2 playerBounding, float pl_rot, Player& player);

    // Draw the asteroid
    void draw() override;

    // Set speed towards a target
    void setSpeedTowards(Vector2 target, float baseSpeed);

    // Spawns an asteroid at a random edge
    void spawnAtEdge();

    // Handles asteroid spawning after destruction
    void spawnNewAsteroid(Vector2 playerPos, float baseSpeed);

    // Update asteroid state, check collisions, and respawn if necessary
    void update(float deltaTime, Vector2 playerPos, float baseSpeed, Player& player, std::vector<std::unique_ptr<Asteroids>>& asteroidsList);
    void update(float deltaTime) override;
};
