#include "Asteroids.h"

// Constructor
Asteroids::Asteroids(Vector2 pos, Vector2 speed) : Enemy(pos, speed, 0){
    asterScale = (GetRandomValue(85, 150) / 100.0f);
    enemy_health = static_cast<int>(20 * asterScale);
    asterDmg = static_cast<int>(10 * asterScale);
    asterSize = static_cast<int>(30 * asterScale);
}

// Setters
void Asteroids::setEnemyPos(Vector2 pos)        {enemy_pos = pos;}
void Asteroids::setEnemySpeed(Vector2 speed)    {enemy_speed = speed;}
void Asteroids::setEnemyHealth(int health)      {enemy_health = health;}

// Getters
int Asteroids::getAsteroidsDamage()     const {return asterDmg;}
float Asteroids::getAsteroidsScale()    const {return asterScale;}
int Asteroids::getAsteroidsSize()       const {return asterSize;}

void Asteroids::movement(float deltaTime) {
    enemy_pos.x += enemy_speed.x * deltaTime;
    enemy_pos.y += enemy_speed.y * deltaTime;

    if (enemy_pos.x < 0) enemy_pos.x = GetScreenWidth();
    if (enemy_pos.x > GetScreenWidth()) enemy_pos.x = 0;
    if (enemy_pos.y < 0) enemy_pos.y = GetScreenHeight();
    if (enemy_pos.y > GetScreenHeight()) enemy_pos.y = 0;
}

void Asteroids::draw() {
    DrawCircleV(enemy_pos, asterSize, GRAY);
}

void Asteroids::update(float deltaTime) {
    movement(deltaTime);
    draw();
}
