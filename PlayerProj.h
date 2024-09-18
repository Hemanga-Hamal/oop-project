#ifndef PLAYERPROJ_H
#define PLAYERPROJ_H
#include "raylib.h"
#include "Projectiles.h"


class PlayerProj : protected Projectiles{
    private:
    Color PlayerProjCol = BLUE;

    public:
    PlayerProj(Vector2 pos,Vector2 speed);
    ~PlayerProj();

    void setProjPos(Vector2);
    void setProjDamage(int);
    void setProjSpeed(Vector2);

    //Render
    void draw() = 0;
    //Update
    void update() = 0;

};
#endif
