#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerProj.h"
#include "raylib.h"
#include <vector>

class Player {
private:
    //Location
    Vector2 pl_pos;
    Vector2 pl_speed = {0.0f, 0.0f};
    float pl_rot = 0;

    //Stats
    int pl_health;

    //Bounding ellipse
    Vector2 pl_BoundingBox = {10.0f, 20.0f};

    //Player vertices
    Vector2 v1;
    Vector2 v2; 
    Vector2 v3;

    //Movement
    float maxSpeed = 300.0f;
    Vector2 pl_acceleration = {0.0f, 0.0f};
    float accelerationRate = 500.0f;
    float friction = 0.01f;

    //Shoot
    std::vector<PlayerProj> projectiles;
    int maxProjectiles = 10; //onscreen 
    int activeBulletCount; 
    float pl_shootTimeRemaining = 0.0f;
    float pl_shootdelay = 0.3f;

    //Damage indicator
    Color pl_colour;
    float pl_flashRedTimeRemaining = 0.0f;
    float flashRedDuration = 0.5f;

public:
    // Constructor and Destructor
    Player(Vector2 Pos, int health);
    ~Player();

    // Setters
    void setPLHealth(int health);
    void setPLSpeed(const Vector2& speed);
    void setRotation(float rotation);

    // Getters
    Vector2 getPLPos() const;
    Vector2 getPLSpeed() const;
    Vector2 getBoundingBox() const;
    Vector2 getPlayershotDir() const;
    int getPLHealth() const;
    int getActiveBulletCount() const;
    float getRotation() const;

    // Movement
    void movement(float deltaTime);

    //Shoot
    void decrementBulletCount();
    std::vector<PlayerProj>& getProjectiles();
    void shoot();

    //Collision logic
    bool checkColEnemy(Vector2 enemyPos, Vector2 enemyBounding);

    // Update and Rendering
    void takeDamage(int damage);
    void draw();
    void update(float deltaTime);

    //Updates within updates
    void updateRotation(Vector2 mousePos);
};

#endif