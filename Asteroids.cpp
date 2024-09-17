#include "Asteroids.h"
#include "raylib.h"
#include "Player.h"

Asteroids::Asteroids(int scale, int damage, float xPos, float yPos, float xSpeed, float ySpeed, float rotation, int health): asteroids_scale(scale), asteroids_damage(damage), Enemy(xPos, yPos, xSpeed, ySpeed, rotation, health) {}

void Asteroids::setAsteroidsDamage(int damageValue){
    asteroids_damage = damageValue;
}

void Asteroids::setAsteroidsScale(int scaleValue){
    asteroids_scale = scaleValue;
}

void Asteroids::setEnemyHealth(int healthValue){
    enemy_health = healthValue;
}

// NEED TO FIX SETENEMYSPEED
        void Asteroids::setEnemySpeed(float x, float y){
            enemy_speed = {x,y};
            enemy_pos.x += 
        }
// NEED TO FIX SETENEMYSPEED

void Asteroids::setEnemyPos(Vector2 vec2){
    enemy_pos.x = vec2.x;
    enemy_pos.y = vec2.y;
}

void Asteroids::setEnemyRotation(float rotationValue){
    enemy_rot = rotationValue;
}

int Asteroids::getAsteroidsDamage(){
    return asteroids_damage;
}

int Asteroids::getAsteroidsScale(){
    return asteroids_scale;
}

// NEED TO DO DRAW AND UPDATE FUNCTIONS
        void draw(){

        }

        void update(float deltaTime){

        }
// NEED TO DO DRAW AND UPDATE FUNCTIONS