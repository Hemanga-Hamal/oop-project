#include "raylib.h"
#include "Player.h"

int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Player Test");

    // Initialize player
    Player player(screenWidth / 2.0f, screenHeight / 2.0f, {100.0f, 100.0f}, 0.0f, 100);

    SetTargetFPS(60);

    // Game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update player
        player.update(deltaTime);

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw player
        player.draw();

        // Draw text
        DrawText("Player Test", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
