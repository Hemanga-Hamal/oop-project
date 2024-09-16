#include "raylib.h"
#include "Player.h"

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Player Test");

    // Create a Player instance
    Player player(screenWidth / 2.0f, screenHeight / 2.0f, 100, {2.0f, 2.0f}, 10);

    SetTargetFPS(60); // Set the desired frame rate

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        player.update();

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        player.draw();

        DrawText("Player Test", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
