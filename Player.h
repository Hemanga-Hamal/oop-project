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

    //player vertices
    Vector2 v1;
    Vector2 v2; 
    Vector2 v3;
    int pl_flashRedFrames;
public:
    // Constructor and Destructor
    Player(float x, float y, Vector2 speed, float rotation, int health, int flashRedFrames);
    ~Player();

    // Setters
    void setPLHealth(int health);
    void setPLSpeed(const Vector2& speed);
    void setRotation(float rotation);

    // Getters
    Vector2 getPLPos() const;
    Vector2 getPLSpeed() const;
    Vector2 getv1();
    Vector2 getv2();
    Vector2 getv3();
    int getPLHealth() const;
    float getRotation() const;

    // Movement
    void up(float deltaTime);
    void down(float deltaTime);
    void left(float deltaTime);
    void right(float deltaTime);

    //Collision logic
    bool checkColEnemy(Vector2);

    // Update and Rendering
    void draw();
    void update(float deltaTime);

    //Updates within updates
    void updateRotation(Vector2 mousePos);
};

#endif