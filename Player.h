#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
private:
    // Location
    Vector2 pl_pos;
    Vector2 pl_speed = {100.0f, 100.0f};
    float pl_rot = 0;

    // Stats
    int pl_health;

    // Bounding ellipse
    Vector2 pl_BoundingBox = {10.0f, 20.0f};

    //player vertices
    Vector2 v1;
    Vector2 v2; 
    Vector2 v3;

    //damage indicator
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
    int getPLHealth() const;
    float getRotation() const;

    // Movement
    void movement(float deltaTimee);

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