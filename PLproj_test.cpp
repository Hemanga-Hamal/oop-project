#include "raylib.h"
#include "Player.h"     
#include "PlayerProj.h" 

int main() {
    // Initialize the window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Player and Projectiles Test");

    // Initialize the player
    Vector2 playerPosition = { 400.0f, 300.0f };
    Player player(playerPosition, 100);

    SetTargetFPS(60); 

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();
        player.update(deltaTime);

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        player.draw();

        // Display active bullet count
        int activeBulletCount = player.getActiveBulletCount();
        DrawText(TextFormat("Active Bullets: %d", activeBulletCount), 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Deinitialize the window
    CloseWindow();

    return 0;
}
