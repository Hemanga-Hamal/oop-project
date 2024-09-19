#include "raylib.h"
#include "PlayerProj.h"

// setters 
void PlayerProj::setProjDamage(int damage)     {damage = proj_damage;}
void PlayerProj::setProjSpeed(Vector2 speed)     {speed = proj_speed;}
void PlayerProj::setProjPos(Vector2 pos)             {pos = proj_pos;}

void 
    proj_pos.x += proj_speed.x *deltatime;
    proj_pos.y += proj_speed.y *deltatime;