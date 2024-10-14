#ifndef CHARGEALIEN_H
#define CHARGEALIEN_H


#include "Alien.h"

class ChargeAlien : public Alien{
private: 
    //Stats
    int health = 1;
    Vector2 speed = {150, 150};
    
    //State
    bool active = true;

    //Movement
    float initialSpeed = 100.0f;
    float chargeSpeed = 400.0f;
    bool detect = false; //Plan is to have the alien float on screen, wait
    //then charge at player

    //Model
    Vector2 alien_size = {15, 15};
    int alien_rotation = 0;
    Color alien_color = RED;

    //Collision
    Vector2 alien_collision_box = {15, 15};

public:
    //Constructor and Destructor
    ChargeAlien(Vector2 Pos);
    ~ChargeAlien();

    //Setters
    void setEnemyPos(Vector2 newPos) override;
    void setEnemySpeed(Vector2 newSpeed) override;
    void setEnemyHealth(int newHealth) override;
    void setChargeSize(Vector2 newSize);
    void setCollisionBox(Vector2 newBox) override;
    void setChargeRotation(int newRotation);
    void setBoolActive(bool newActive);
    void setDetectActive(bool newDetect);

    //Getters
    Vector2 getAlienSize();
    Vector2 getCollisionBox();
    int getAlienRotation();
    bool getBoolActive();
    bool getDetectActive();

    //Collision Detection
    bool checkCollisionBox(Vector2 entitypos, Vector2 entitybox);
    
    //Movement
    void movement(float deltaTime) override;
    void movement(float deltaTime, Vector2 playerPos);
    void setSpeedTowards(Vector2 target, float baseSpeed);

    //Update and Rendering
    void draw() override;
    void update(float deltaTime) override;
    void update(float deltaTime, Vector2 playerPos);
    void spawnAtEdge();
};

#endif