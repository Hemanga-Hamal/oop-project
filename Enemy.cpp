#include "Enemy.h"
#include "raylib.h"

Enemy::Enemy() {}

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