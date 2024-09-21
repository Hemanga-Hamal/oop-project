#include "raylib.h"
#include "raymath.h"
#include "Player.h"
#include "Asteroids.h"
#include <vector>

int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Asteroids Test");

    // Initialize player
    Player player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);

    // Initialize a vector to store multiple asteroids
    std::vector<Asteroids*> asteroids;

    // Create initial set of asteroids
    for (int i = 0; i < 5; i++) {
        Asteroids* newAsteroid = new Asteroids({0.0f, 0.0f}, {0.0f, 0.0f});
        newAsteroid->spawnNewAsteroid(player.getPLPos(), 150.0f);
        asteroids.push_back(newAsteroid);
    }

    SetTargetFPS(60);

    // Game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update player
        player.update(deltaTime);

        // Update all asteroids and handle collisions automatically
        for (Asteroids* asteroid : asteroids) {
            asteroid->update(deltaTime, player.getPLPos(), 150.0f, player);
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw player
        player.draw();

        // Draw all asteroids
        for (Asteroids* asteroid : asteroids) {
            asteroid->draw(); // Already handled in update, but for clarity
        }

        // Display player health
        DrawText(TextFormat("Player Health: %i", player.getPLHealth()), 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Cleanup dynamically allocated asteroids
    for (Asteroids* asteroid : asteroids) {
        delete asteroid;
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
