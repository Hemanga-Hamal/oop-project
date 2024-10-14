#ifndef DYNAMICPLAYERPROJ_H
#define DYNAMICPLAYERPROJ_H

#include "PlayerProj.h"

class DynamicPlayerProj {
private:
    PlayerProj* proj; 

public:
    // Constructor
    DynamicPlayerProj(Vector2 pos, Vector2 speed);

    // Destructor
    ~DynamicPlayerProj();

    // Setters
    void setProjPos(Vector2 pos);
    void setProjSpeed(Vector2 speed);
    void setProjDamage(int damage);

    // Getters
    Vector2 getProjPos() const;
    Vector2 getProjSpeed() const;
    int getProjDamage() const;
    bool isActive() const;

    // Collision
    bool EnemyCollisionCheck(Vector2 enemy_pos, Vector2 enemy_bounding);
    
    // Update and Render
    void update(float deltaTime);
    void draw();
};

#endif
