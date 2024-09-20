#include "PlayerProj.h"
#include "raymath.h"

// Constructor and destructor
PlayerProj::PlayerProj(Vector2 pos, Vector2 speed) :Projectiles(pos, speed, 0) {}


// setters 
void PlayerProj::setProjDamage(int damage)     {damage = proj_damage;}
void PlayerProj::setProjSpeed(Vector2 speed)     {speed = proj_speed;}
void PlayerProj::setProjPos(Vector2 pos)             {pos = proj_pos;}

void PlayerProj::update(float deltaTime){
    proj_pos.x += proj_speed.x *deltaTime;
    proj_pos.y += proj_speed.y *deltaTime;
}

void PlayerProj::draw() {
    float ProjLength = 10.0f;
    
    Vector2 ProjEnd = {
        proj_pos.x + proj_speed.x * (ProjLength / Vector2Length(proj_speed)),
        proj_pos.y + proj_speed.y * (ProjLength / Vector2Length(proj_speed))
    };

    DrawLineV(proj_pos, ProjEnd, PlayerProjCol);
}

