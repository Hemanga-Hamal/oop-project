#include "PlayerProj.h"
#include "raymath.h"

// Constructor and destructor
PlayerProj::PlayerProj(Vector2 pos, Vector2 speed) : Projectiles(pos, speed, 10) {}

// Setters
void PlayerProj::setProjDamage(int damage)     { proj_damage = damage; }
void PlayerProj::setProjSpeed(Vector2 speed)   { proj_speed = speed; }
void PlayerProj::setProjPos(Vector2 pos)       { proj_pos = pos; }

void PlayerProj::update(float deltaTime) {
    proj_pos.x += proj_speed.x * deltaTime;
    proj_pos.y += proj_speed.y * deltaTime;
}

void PlayerProj::draw() const {
    float ProjLength = 10.0f;

    float speedLength = Vector2Length(proj_speed);
    if (speedLength > 0) {
        Vector2 ProjEnd = {
            proj_pos.x + proj_speed.x * (ProjLength / speedLength),
            proj_pos.y + proj_speed.y * (ProjLength / speedLength)
        };

        DrawLineV(proj_pos, ProjEnd, PlayerProjCol);
    }
}
