#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
class Player {
protected:
    //location
    Vector2 pl_pos;
    Vector2 pl_speed;

    //stats
    int pl_health;
    int pl_projdmg;

public:
    Player(float, float, int, Vector2, int);
    ~Player();

    //set
    void setPLHealth(int);
    void setPLSpeed( Vector2&);
    void setPLProjDmg(int);

    //get
    Vector2 getPLPos();
    Vector2 getPLSpeed();
    int getPLHealth();
    int getPLProjDmg();

    //v0->prototyping {rendering}
   void draw();
    void update();
    
};

#endif