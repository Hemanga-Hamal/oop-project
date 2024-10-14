#include "ChargeAlien.h"
#include "raymath.h"
#include <cstdlib>

//Constructor and Destructor
ChargeAlien::ChargeAlien(Vector2 pos) : Alien(pos, {0,0}, 1){
    enemy_health = health;
    enemy_speed = speed;
    detect = false; 
}
ChargeAlien::~ChargeAlien() {}

//Setters
void ChargeAlien::setEnemyPos(Vector2 newPos) { enemy_pos = newPos; }
void ChargeAlien::setEnemySpeed(Vector2 newSpeed) { enemy_speed = newSpeed; }
void ChargeAlien::setEnemyHealth(int newHealth) { enemy_health = newHealth; }
void ChargeAlien::setChargeSize(Vector2 newSize) { alien_size= newSize; }
void ChargeAlien::setCollisionBox(Vector2 newBox) { alien_collision_box = newBox; }
void ChargeAlien::setChargeRotation(int newRotation) { alien_rotation = newRotation; }
void ChargeAlien::setBoolActive(bool newActive) { active = newActive; }
void ChargeAlien::setDetectActive(bool newDetect) { detect = newDetect; }

//Getters
Vector2 ChargeAlien::getAlienSize()         {return alien_size; }
Vector2 ChargeAlien::getCollisionBox()      {return alien_collision_box; }
int ChargeAlien::getAlienRotation()         {return alien_rotation; }
bool ChargeAlien::getBoolActive()           {return active; }
bool ChargeAlien::getDetectActive()         {return detect; }

//Collision Detection
bool ChargeAlien::checkCollisionBox(Vector2 entityPos, Vector2 entityBox) {
    if (!active) return false;
    Vector2 relativePos = Vector2Subtract(enemy_pos, entityPos);
    Vector2 rotatedPos = Vector2Rotate(relativePos, -alien_rotation * DEG2RAD); 
    bool insideBox = (rotatedPos.x >= -alien_collision_box.x / 2 && rotatedPos.x <=alien_collision_box.x / 2 
                     && rotatedPos.y >= -alien_collision_box.y / 2 && rotatedPos.y <= alien_collision_box.y / 2);
    return insideBox;
}

//Movement Logic
void ChargeAlien::movement(float deltaTime) {
    Vector2 defaultPlayerPos = {0, 0};
    movement(deltaTime, defaultPlayerPos);
}

//Setting Target
void ChargeAlien::setSpeedTowards(Vector2 target, float baseSpeed) {
    if (!detect) return;

    Vector2 direction = Vector2Subtract(target, enemy_pos);
    direction = Vector2Normalize(direction);
    setEnemySpeed(Vector2Scale(direction, chargeSpeed));
}

//Detection Logic


//Drawing butterflies
void ChargeAlien::draw() {
    DrawRectangleV(enemy_pos, alien_size, alien_color);
}

//Update
void ChargeAlien::update(float deltaTime) {
    Vector2 defaultPlayerPos = {0, 0};
    update(deltaTime, defaultPlayerPos);
}

void ChargeAlien::update(float deltaTime, Vector2 playerPos){
    movement(deltaTime, playerPos);
    draw();
}

void ChargeAlien::spawnAtEdge() {
    int edgeCase = std::rand() % 4;
    switch (edgeCase) {
        case 0:
            enemy_pos.x = static_cast<float>(std::rand() % GetScreenWidth());
            enemy_pos.y = 0; // Top
            break;
        case 1:
            enemy_pos.x = static_cast<float>(std::rand() % GetScreenWidth());
            enemy_pos.y = GetScreenHeight(); // Bottom
            break;
        case 2:
            enemy_pos.x = 0; // Left
            enemy_pos.y = static_cast<float>(std::rand() % GetScreenHeight());
            break;
        case 3:
            enemy_pos.x = GetScreenWidth(); // Right
            enemy_pos.y = static_cast<float>(std::rand() % GetScreenHeight());
            break;
    }
    setDetectActive(true);
}
