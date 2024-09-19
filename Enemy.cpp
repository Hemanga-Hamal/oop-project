#include "Enemy.h"

//Constructor
Enemy::Enemy(Vector2 pos, Vector2 speed, int health)
     : enemy_pos(pos), enemy_speed(speed), enemy_health(health){}

//Destructor
Enemy::~Enemy() {}

//Getters
Vector2 Enemy::getEnemyPos()        {return enemy_pos;      }
Vector2 Enemy::getEnemySpeed()      {return enemy_speed;    }
int Enemy::getEnemyHealth()         {return enemy_health;   }