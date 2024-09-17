#include "Enemy.h"
#include "raylib.h"

Enemy::Enemy() {}

int Enemy::getEnemyHealth() {
    return enemy_health;
}

int Enemy::getEnemySpeed() {
    return enemy_speed;
}


 // Getters
        int getEnemyHealth();
        Vector2 getEnemySpeed();
        Vector2 getEnemyPos();
        float getEnemyRotation();
        // Updating and Rendering
        void draw();
        void update(float deltaTime);