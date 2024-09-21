#include "PlayerProj.h"
#include "raymath.h"

// Constructor and destructor
PlayerProj::PlayerProj(Vector2 pos, Vector2 speed_raw) :Projectiles(pos, speed_raw, 15) , active(true) {
    Vector2 direction = {0,0};
    direction.x = speed_raw.x* (ProjSetSpeed/Vector2Length(speed_raw));
    direction.y = speed_raw.y* (ProjSetSpeed/Vector2Length(speed_raw));
    this->proj_speed = direction;
}

PlayerProj::~PlayerProj() {}

// setters 
void PlayerProj::setProjDamage(int damage)     {proj_damage = damage;}
void PlayerProj::setProjSpeed(Vector2 speed)     {proj_speed = speed;}
void PlayerProj::setProjPos(Vector2 pos)             {proj_pos = pos;}

// Check for edge collision
bool PlayerProj::checkEdgeCollision() {
    if (proj_pos.x < 0 || proj_pos.x > GetScreenWidth() ||
        proj_pos.y < 0 || proj_pos.y > GetScreenHeight()) {
        active = false; 
        return true;    
    }
    return false;
}

// Update and Render
void PlayerProj::update(float deltaTime) {
    proj_pos.x += proj_speed.x * deltaTime;
    proj_pos.y += proj_speed.y * deltaTime;

    if (checkEdgeCollision()) {
        active = false;
    }
}

void PlayerProj::draw() {
    Vector2 ProjEnd = {
        proj_pos.x + proj_speed.x * (ProjLength / Vector2Length(proj_speed)),
        proj_pos.y + proj_speed.y * (ProjLength / Vector2Length(proj_speed))
    };
    DrawLineEx(proj_pos, ProjEnd, lineThickness, PlayerProjCol);
}