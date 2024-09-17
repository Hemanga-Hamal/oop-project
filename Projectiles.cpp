#include "raylib.h"
#include "Projectiles.h"

// Constructor and Destructor
Projectiles::Projectiles() {}

//Getters
Vector2 Projectiles::getProjPos()   {return proj_pos;}
Vector2 Projectiles::getProjSpeed() {return proj_speed;}
int Projectiles::getProjDamage()    {return proj_damage;}