#include "raylib.h"
#include "Player.h"

class Enemy {
private:
    Vector2 position;
    float radius;
    int damage;
public:
    Enemy(float x, float y, float r, int damage): position({x, y}), radius(r), damage(damage){}
    
    Vector2 getEnemyPos()   {return position;   }
    float getEnemyRadius()  {return radius;     }
    int getEnemyDamage()    {return damage;     }

    void draw()     {DrawCircleV(position, radius, RED);}
};


int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Player Test");

    // Initialize player and enemy
    Player player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);
    Enemy enemy(screenWidth / 4.0f, screenHeight / 4.0f, 25.0f, 10);

    SetTargetFPS(60);

    // Game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update player with enemy position and radius
        player.update(deltaTime);
        
        // Collision detected: handle damage or response
        if (player.checkColEnemy(enemy.getEnemyPos(), enemy.getEnemyRadius())) {
            player.takeDamage(enemy.getEnemyDamage());
        }

        // Drawing - background
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw player and enemy (with bounding circle)
        player.draw();
        enemy.draw();

        // Display player health
        DrawText(TextFormat("Player Health: %i", player.getPLHealth()), 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
