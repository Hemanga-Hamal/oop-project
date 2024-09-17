#include "Enemy.h"
#include "raylib.h"

Enemy::Enemy(float xPos, float yPos, float xSpeed, float ySpeed, float rotation, int health): enemy_pos({xPos, yPos}), enemy_speed({xSpeed, ySpeed}), enemy_rot(rotation), enemy_health(health) {}

int Enemy::getEnemyHealth() {
    return enemy_health;
}

Vector2 Enemy::getEnemySpeed() {
    return enemy_speed;
}

Vector2 Enemy::getEnemyPos() {
    return enemy_pos;
}

float Enemy::getEnemyRotation() {
    return enemy_rot;
}