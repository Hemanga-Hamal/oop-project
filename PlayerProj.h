#ifndef PLAYERPROJ_H
#define PLAYERPROJ_H
#include "raylib.h"
#include "Projectiles.h"


class PlayerProj : protected Projectiles{
private:
    //stats
    float ProjLength = 10.0f;
    float ProjSetSpeed = 100.0f;

    //tag
    bool active;

    //model
    float lineThickness = 3.0f;
    Color PlayerProjCol = BLUE;

public:
    // Constructor and Destructor
    PlayerProj(Vector2 pos, Vector2 speed);
    ~PlayerProj();

    //setters
    void setProjPos(Vector2);
    void setProjSpeed(Vector2);
    void setProjDamage(int);

    //Collision
    bool checkEdgeCollision();

    //Update and Render
    void update(float deltaTime);
    void draw();

};
#endif
