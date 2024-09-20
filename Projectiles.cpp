#include "raylib.h"
#include "Projectiles.h"

// Constructor and Destructor
Projectiles::Projectiles(Vector2 pos, Vector2 speed,  int damage) : proj_pos(pos), proj_speed(speed), proj_damage(damage) {}
Projectiles::~Projectiles() {}


//Getters
Vector2 Projectiles::getProjPos()   const {return proj_pos;}
Vector2 Projectiles::getProjSpeed() const {return proj_speed;}
int Projectiles::getProjDamage()    const {return proj_damage;}