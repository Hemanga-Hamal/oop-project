#include "DynamicPlayerProj.h"

// Constructor
DynamicPlayerProj::DynamicPlayerProj(Vector2 pos, Vector2 speed) {
    proj = new PlayerProj(pos, speed);
}

// Destructor
DynamicPlayerProj::~DynamicPlayerProj() {
    delete proj;  // Free memory
}

// Setters
void DynamicPlayerProj::setProjPos(Vector2 pos) {
    proj->setProjPos(pos);
}

void DynamicPlayerProj::setProjSpeed(Vector2 speed) {
    proj->setProjSpeed(speed);
}

void DynamicPlayerProj::setProjDamage(int damage) {
    proj->setProjDamage(damage);
}

// Getters
Vector2 DynamicPlayerProj::getProjPos() const {
    return proj->getProjPos();
}

Vector2 DynamicPlayerProj::getProjSpeed() const {
    return proj->getProjSpeed();
}

int DynamicPlayerProj::getProjDamage() const {
    return proj->getProjDamage();
}

bool DynamicPlayerProj::isActive() const {
    return proj->isActive();
}

// Collision
bool DynamicPlayerProj::EnemyCollisionCheck(Vector2 enemy_pos, Vector2 enemy_bounding) {
    return proj->EnemyCollisionCheck(enemy_pos, enemy_bounding);
}

// Update and Render
void DynamicPlayerProj::update(float deltaTime) {
    proj->update(deltaTime);
}

void DynamicPlayerProj::draw() {
    proj->draw();
}
