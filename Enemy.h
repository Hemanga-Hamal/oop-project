#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

class Enemy{
    protected:
        //Enemy stats
        Vector2 enemy_pos;
        Vector2 enemy_speed;
        int enemy_health;

    public:
        //Constructor
        Enemy(Vector2 Pos, Vector2 Speed,int Health);

        //Destructor
        virtual ~Enemy();

        //Setters
        void virtual setEnemyPos(Vector2) = 0;
        void virtual setEnemySpeed(Vector2) = 0;
        void virtual setEnemyHealth(int) = 0;

        //Getters
        Vector2 getEnemyPos();
        Vector2 getEnemySpeed();
        int getEnemyHealth();

        //Movement
        void virtual movement(float) = 0;

        //Updating and Rendering
        void virtual draw() = 0;
        void virtual update(float deltaTime) = 0;
};

#endif