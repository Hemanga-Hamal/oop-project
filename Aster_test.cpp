#include "raylib.h"
#include "raymath.h"
#include "Player.h"
#include "Asteroids.h"

int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Asteroids Test");

    // Initialize player and first asteroid
    Player player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);
    Asteroids asteroid({screenWidth / 4.0f, screenHeight / 4.0f}, {0.0f, 0.0f});
    asteroid.setSpeedTowards(player.getPLPos(), 150.0f);

    SetTargetFPS(60);

    // Game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update asteroid and player
        asteroid.update(deltaTime);
        player.update(deltaTime);

        // Collision detection
        if (asteroid.checkColPlayer(player.getPLPos(), player.getBoundingBox(), 0.0f)) {
            player.takeDamage(asteroid.getAsteroidsDamage());
            
            // Create new asteroid position off-screen and reset
            Vector2 newAsteroidPos = { (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) };
            if (newAsteroidPos.x < screenWidth / 2) newAsteroidPos.x -= screenWidth;
            if (newAsteroidPos.y < screenHeight / 2) newAsteroidPos.y -= screenHeight;

            // Reset the asteroid with a new position and speed
            asteroid.reset(newAsteroidPos, player.getPLPos(), 100.0f);
        }

        // Check if the asteroid is inactive and needs resetting (e.g., if it's off-screen)
        if (!asteroid.isActive()) {
            Vector2 newAsteroidPos = { (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) };
            if (newAsteroidPos.x < screenWidth / 2) newAsteroidPos.x -= screenWidth;
            if (newAsteroidPos.y < screenHeight / 2) newAsteroidPos.y -= screenHeight;

            asteroid.reset(newAsteroidPos, player.getPLPos(), 100.0f);
        }

        // Drawing - background
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw player and asteroid
        player.draw();
        asteroid.draw();

        // Display player health
        DrawText(TextFormat("Player Health: %i", player.getPLHealth()), 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
