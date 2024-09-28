#ifndef SCOUTALIEN_H
#define SCOUTALIEN_H

#include "Enemy.h"

class ScoutAlien : public Enemy {
private:
    //flag
    bool active = true;

    //movement
    float detectionRange = 200.0f;
    float randomMoveTimer;
    bool escapeMode = false;
    
    //model
    Vector2 size = {10,10};
    int rotation = 0;
    Color color = RED;

    //collision
    Vector2 collisionBox = {10,10};

public:
    //Constructor and Destructor
    ScoutAlien(Vector2 Pos, Vector2 Speed, int Health);
    ~ScoutAlien();

    //Setters
    void setScoutSize(Vector2 newSize);
    void setcollisionBox(Vector2 newBox);
    void setScoutRotation(int newRotation);

    //Getters
    Vector2 getScoutSize();
    Vector2 getcollisionBox();
    int getScoutRotation();

    //collision
    bool CheckCollisionBoxes(Vector2 entityPos, Vector2 entityBox);

    //Movement
    float escapeSpeed = 300.0f;
    void movement(float deltaTime, Vector2 playerPos);

    //Updating and Rendering
    void draw();
    void update(float deltaTime, Vector2 PlayerPos);

};

#endif
