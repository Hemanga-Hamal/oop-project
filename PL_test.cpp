#include "raylib.h"
#include "Player.h"

class Enemy {
private:
    Vector2 position;  // Enemy's position
    float radius;      // Radius of the bounding circle

public:
    Enemy(float x, float y, float r) 
        : position({x, y}), radius(r) {}

    Vector2 getEnemyPos(){
        return position;
    }

    float getEnemyRadius(){
        return radius;
    }

    void draw() {
        DrawCircleV(position, radius, RED);
        DrawCircleLines(position.x, position.y, radius, DARKGRAY);
    }
};


int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Player Test");

    // Initialize player and enemy
    Player player(screenWidth / 2.0f, screenHeight / 2.0f, {100.0f, 100.0f}, 0.0f, 100);
    int damage = 10;
    Enemy enemy(screenWidth / 4.0f, screenHeight / 4.0f, 25.0f);  // Radius = 25.0f

    SetTargetFPS(60);

    // Game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update player with enemy position and radius
        player.update(deltaTime);
        // Collision detected: handle damage or response
        if (player.checkColEnemy(enemy.getEnemyPos(), enemy.getEnemyRadius())) {
            player.takeDamage(damage);
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
