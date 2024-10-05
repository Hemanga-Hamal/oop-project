#ifndef SCOUTALIEN_H
#define SCOUTALIEN_H

#include "Enemy.h"

class ScoutAlien : public Enemy {
private:
    // Stats
    int health = 1;
    Vector2 speed = {150, 150};

    // Flag
    bool active = true;

    // Movement
    float escapeSpeed = 300.0f;
    float detectionRange = 200.0f;
    float randomMoveTimer;
    bool escapeMode = false;
    
    // Model
    Vector2 size = {15, 15};
    int rotation = 0;
    Color color = RED;

    // Collision
    Vector2 collisionBox = {15, 15};

public:
    // Constructor and Destructor
    ScoutAlien(Vector2 Pos);
    ~ScoutAlien();

    // Setters (Override pure virtual functions from Enemy)
    void setEnemyPos(Vector2 newPos) override;
    void setEnemySpeed(Vector2 newSpeed) override;
    void setScoutSize(Vector2 newSize);
    void setcollisionBox(Vector2 newBox);
    void setEnemyHealth(int newHealth) override;
    void setScoutRotation(int newRotation);
    void setboolactive(bool newActive);
    void setEscapeMode(bool newMode);

    // Getters
    Vector2 getScoutSize();
    Vector2 getcollisionBox();
    int getScoutRotation();
    bool getboolactive();
    bool getEscapeMode();

    // Collision detection
    bool CheckCollisionBoxes(Vector2 entityPos, Vector2 entityBox);

    // Movement
    void movement(float deltaTime) override;  // For overriding the virtual function
    void movement(float deltaTime, Vector2 playerPos); 

    // Updating and Rendering
    void draw() override;
    void update(float deltaTime) override;  // For overriding the virtual function
    void update(float deltaTime, Vector2 PlayerPos);
};

#endif
