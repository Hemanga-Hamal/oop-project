#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "raylib.h"

class Projectiles {
protected:
    // Stats
    Vector2 proj_pos;
    Vector2 proj_speed;
    int proj_damage;

public:
    // Constructor and Destructor
    Projectiles(Vector2 pos, Vector2 speed, int damage);
    virtual ~Projectiles();

    // Setters
    virtual void setProjPos(Vector2) = 0;
    virtual void setProjDamage(int) = 0;
    virtual void setProjSpeed(Vector2) = 0;
    
    // Getters
    Vector2 getProjSpeed() const;
    Vector2 getProjPos() const;
    int getProjDamage();

    //Collision
    virtual bool EnemyCollisionCheck(Vector2 enemy_pos, Vector2 enempy_bounding) = 0;

    // Render
    virtual void draw() = 0;

    // Update
    virtual void update(float deltaTime) = 0;
};

#endif
