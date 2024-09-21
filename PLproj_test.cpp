#include "raylib.h"
#include "PlayerProj.h"

int main() {
    // Initialize the window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "PlayerProj Test");

    // Initialize the projectile
    Vector2 initialPosition = { 400.0f, 300.0f };  // Center of the screen
    Vector2 speed = { 100.0f, 50.0f };             // Initial speed
    PlayerProj playerProj(initialPosition, speed);

    SetTargetFPS(60);  // Set FPS to 60

    // Main game loop
    while (!WindowShouldClose()) {
        // Update projectile
        float deltaTime = GetFrameTime();
        playerProj.update(deltaTime);

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw projectile
        playerProj.draw();

        EndDrawing();
    }

    // Deinitialize the window
    CloseWindow();

    return 0;
}
