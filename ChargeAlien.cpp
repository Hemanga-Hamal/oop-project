#include "raylib.h"
#include "ChargeAlien.h"

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
Vector2 ChargeAlien::getChargeSize()         {return alien_size; }







