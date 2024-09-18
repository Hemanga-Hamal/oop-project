#include "Asteroids.h"

Asteroids::Asteroids(int scale, int damage, Vector2 pos, Vector2 speed, int health)
    : asteroids_scale(scale), asteroids_damage(damage), Enemy(pos, speed, health) {}


//Setters
void Asteroids::setAsteroidsDamage(int damageValue)     {asteroids_damage = damageValue;}
void Asteroids::setAsteroidsScale(int scaleValue)       {asteroids_scale = scaleValue;  }
void Asteroids::setEnemyHealth(int healthValue)         {enemy_health = healthValue;    }

// NEED TO FIX SETENEMYSPEED
void Asteroids::setEnemySpeed(float x, float y){}

// NEED TO FIX SETENEMYSPEED
void Asteroids::setEnemyPos(Vector2 vec2){
    enemy_pos.x = vec2.x;
    enemy_pos.y = vec2.y;
}

//Getters
int Asteroids::getAsteroidsDamage()                     {return asteroids_damage;}
int Asteroids::getAsteroidsScale()                      {return asteroids_scale;}

// NEED TO DO DRAW AND UPDATE FUNCTIONS
void draw(){}
void update(float deltaTime){}