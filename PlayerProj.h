#ifndef PLAYERPROJ_H
#define PLAYERPROJ_H
#include "raylib.h"
#include "Projectiles.h"

class PlayerProj : public Projectiles{
private:
    //Stats
    float ProjLength = 10.0f;
    float ProjSetSpeed = 400.0f;

    //State
    bool active;

    //Model
    float lineThickness = 3.0f;
    Color PlayerProjCol = BLUE;

public:
    //Constructor and Destructor
    PlayerProj(Vector2 pos, Vector2 speed);
    ~PlayerProj();

    //Setters
    void setProjPos(Vector2);
    void setProjSpeed(Vector2);
    void setProjDamage(int);

    //Getters
    bool isActive() const;

    //Collision
    bool checkEdgeCollision();
    bool EnemyCollisionCheck(Vector2 enemy_pos, Vector2 enempy_bounding);

    //Render and Update
    void draw();
    void update(float deltaTime);
};
#endif
