#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"

class Enemy{
    protected:
        // Enemy stats
        Vector2 enemy_pos;
        Vector2 enemy_speed;
        float enemy_rot;
        int enemy_health;
    public:
        // Setters
        void virtual setEnemyHealth(int) = 0;
        void virtual setEnemySpeed(int) = 0;
        void virtual setEnemyPos(Vector2) = 0;
        void virtual setEnemyRotation(float) = 0;

        // Getters
        int getEnemyHealth();
        Vector2 getEnemySpeed();
        Vector2 getEnemyPos();
        float getEnemyRotation();

        // Constructor
        Enemy(float, float, float, float, float, int);

        // Destructor
        virtual ~Enemy();

        // Movement
        void virtual movement(float, float) = 0;

        // Updating and Rendering
        void virtual draw() = 0;
        void virtual update(float deltaTime) = 0;
};

#endif