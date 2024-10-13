#ifndef SCOUTALIEN_H
#define SCOUTALIEN_H

#include "Alien.h"

class ScoutAlien : public Alien {
private:
    // Stats
    int health = 1;
    Vector2 speed = {150, 150};

    // Flag
    bool active = true;

    // Movement
    float escapeSpeed = 300.0f;
    float detectionRange = 150.0f;
    float randomMoveTimer;
    bool escapeMode = false;
    
    // Model
    Vector2 size = {15, 15};
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
    void setAlienSize(Vector2 newSize) override;
    void setCollisionBox(Vector2 newBox) override;
    void setEnemyHealth(int newHealth) override;
    void setAlienRotation(int newRotation) override;
    void setBoolActive(bool newActive) override;
    void setEscapeMode(bool newMode);

    // Getters
    Vector2 getScoutSize();
    Vector2 getCollisionBox();
    int getScoutRotation();
    bool getBoolActive() const;
    bool getEscapeMode();

    // Collision detection
    bool checkCollisionBox(Vector2 entityPos, Vector2 entityBox);

    // Movement
    void movement(float deltaTime) override;  // For overriding the virtual function
    void movement(float deltaTime, Vector2 playerPos); 

    // Updating and Rendering
    void draw() override;
    void update(float deltaTime) override;  // For overriding the virtual function
    void update(float deltaTime, Vector2 PlayerPos);
};

#endif
