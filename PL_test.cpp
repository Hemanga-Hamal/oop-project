#include "raylib.h"
#include "Player.h"

class Enemy {
    private:
    Vector2 position;
    float radius;
    
    public:
    Vector2 getEnemyPos(){
        return position;
    }

    Enemy(float x, float y, float r) 
        : position({x, y}), radius(r) {}

    void draw() {
        DrawCircleV(position, radius, RED);
    }
};

int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Player Test");

    // Initialize 
    Player player(screenWidth / 2.0f, screenHeight / 2.0f, {100.0f, 100.0f}, 0.0f, 100, 0);
    Enemy enemy(screenWidth / 4.0f, screenHeight / 4.0f, 25.0f);

    SetTargetFPS(60);

    // Game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update player
        player.update(deltaTime);

        // Drawing - background
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw
        player.draw();
        enemy.draw();
        
        //Player Collision
        player.checkColEnemy(enemy.getEnemyPos());

        // Draw text
        DrawText("Player Test", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
