#include "Alien.h"

//Constructor and Destructor
Alien::Alien(Vector2 pos, Vector2 speed, int health ) 
    : Enemy(pos, speed, health){}

Alien::~Alien(){}

//Getters
Vector2 Alien::getAlienSize()      {return alien_size;          }
Vector2 Alien::getCollisionBox()   {return alien_collision_box; }
int Alien::getAlienRotation()      {return alien_rotation;      }
bool Alien::getBoolActive()        {return alien_active;        }