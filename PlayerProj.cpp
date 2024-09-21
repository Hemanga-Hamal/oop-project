#include "PlayerProj.h"
#include "raymath.h"

// Constructor and destructor
PlayerProj::PlayerProj(Vector2 pos, Vector2 speed) :Projectiles(pos, speed, 0) {}
PlayerProj::~PlayerProj() {}

// setters 
void PlayerProj::setProjDamage(int damage)     {proj_damage = damage;}
void PlayerProj::setProjSpeed(Vector2 speed)     {proj_speed = speed;}
void PlayerProj::setProjPos(Vector2 pos)             {proj_pos = pos;}

void PlayerProj::update(float deltaTime){
    proj_pos.x += proj_speed.x *deltaTime;
    proj_pos.y += proj_speed.y *deltaTime;
}

void PlayerProj::draw() {
    float ProjLength = 10.0f;
    float lineThickness = 3.0f;

    Vector2 ProjEnd = {
        proj_pos.x + proj_speed.x * (ProjLength / Vector2Length(proj_speed)),
        proj_pos.y + proj_speed.y * (ProjLength / Vector2Length(proj_speed))
    };
    DrawLineEx(proj_pos, ProjEnd, lineThickness, PlayerProjCol);
}


