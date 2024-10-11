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

