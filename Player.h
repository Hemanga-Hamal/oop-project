#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
protected:
    // Location
    Vector2 pl_pos;
    Vector2 pl_speed;
    float pl_rot;

    // Stats
    int pl_health;

public:
    // Constructor and Destructor
    Player(float x, float y, Vector2 speed, float rotation, int health);
    ~Player();

    // Setters
    void setPLHealth(int health);
    void setPLSpeed(const Vector2& speed);
    void setRotation(float rotation);

    // Getters
    Vector2 getPLPos() const;
    Vector2 getPLSpeed() const;
    int getPLHealth() const;
    float getRotation() const;

    // Movement
    void up(float deltaTime);
    void down(float deltaTime);
    void left(float deltaTime);
    void right(float deltaTime);

    // Update and Rendering
    void draw() const;
    void update(float deltaTime);

    //Updates within updates
    void updateRotation(Vector2 mousePos);
};

#endif