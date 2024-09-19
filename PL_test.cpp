#include "raylib.h"
#include "Player.h"

class enemy_dummy {
private:
    Vector2 position;
    Vector2 radius;
    int damage;
public:
    enemy_dummy(float x, float y, Vector2 r, int damage): position({x, y}), radius(r), damage(damage){}
    ~enemy_dummy(){}
    
    Vector2 getEnemy_dummyPos()       {return position;   }
    Vector2 getEnemy_dummyRadius()    {return radius;     }
    int getEnemy_dummyDamage()        {return damage;     }

    void draw()     {DrawCircleV(position, radius.x, RED);}
};


int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Player Test");

    // Initialize player and enemy_dummy
    Player player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);
    enemy_dummy enemy(screenWidth / 4.0f, screenHeight / 4.0f, {25.0f, 25.0f}, 10);

    SetTargetFPS(60);

    // Game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update player with enemy_dummy position and radius
        player.update(deltaTime);
        
        // Collision detected: handle damage or response
        if (player.checkColEnemy(enemy.getEnemy_dummyPos(), enemy.getEnemy_dummyRadius())) {
            player.takeDamage(enemy.getEnemy_dummyDamage());
        }

        // Drawing - background
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw player and enemy_dummy (with bounding circle)
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
