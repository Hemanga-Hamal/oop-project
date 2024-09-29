#ifndef PLAYERPROJ_H
#define PLAYERPROJ_H
#include "raylib.h"
#include "Projectiles.h"

class PlayerProj : public Projectiles{
private:
    //stats
    float ProjLength = 10.0f;
    float ProjSetSpeed = 400.0f;

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

    //getter
    bool isActive() const;

    //Collision
    bool checkEdgeCollision();
    bool EnemyCollisionCheck(Vector2 enemy_pos, Vector2 enempy_bounding);

    //Render and Update
    void draw();
    void update(float deltaTime);
};
#endif
