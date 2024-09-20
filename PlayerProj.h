#ifndef PLAYERPROJ_H
#define PLAYERPROJ_H
#include "raylib.h"
#include "Projectiles.h"


class PlayerProj : public Projectiles{
private:
    Color PlayerProjCol = BLUE;
    
public:
    // Constructor and Destructor
    PlayerProj(Vector2 pos, Vector2 speed);
    ~PlayerProj();

    //setters
    void setProjPos(Vector2);
    void setProjSpeed(Vector2);
    void setProjDamage(int);

    //Render and Update
    void draw() const;
    void update(float deltaTime);

};
#endif
