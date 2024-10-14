#ifndef ALIEN_H
#define ALIEN_H

#include "Enemy.h"

class Alien : public Enemy {
protected:
    //State
    bool alien_active = false;

    //Model
    Vector2 alien_size = {15, 15};
    int alien_rotation = 0;
    Color alien_color = WHITE;

    //Collision
    Vector2 alien_collision_box = {20, 20};

public:
    //Constructor and Destructor
    Alien(Vector2 pos, Vector2 speed, int health);
    ~Alien();

    //Setters
    void virtual setCollisionBox(Vector2) = 0;
    void virtual setAlienSize(Vector2) = 0;
    void virtual setAlienRotation(int) = 0;
    void virtual setBoolActive(bool) = 0;
    
    //Getters
    Vector2 getAlienSize();
    Vector2 getCollisionBox();
    int getAlienRotation();
    bool getBoolActive();
    
    //Collision Dectection
    bool checkCollisionBox();
};

#endif