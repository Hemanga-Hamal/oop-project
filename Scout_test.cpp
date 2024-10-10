#include "raylib.h"
#include "ScoutAlien.h"
#include "Player.h"
#include <vector>

// Helper function to reset the game
void ResetGame(Player &player, ScoutAlien &scout, int screenWidth, int screenHeight) {
    player = Player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);
    scout.setEnemyPos({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)});
    scout.setEscapeMode(false);
    scout.setBoolActive(true);
}

// Main function
int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Initialize the window
    InitWindow(screenWidth, screenHeight, "Scout Alien Test");

    // Initialize the player at the center of the screen
    Player player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);

    // Initialize the scout alien at a random position
    ScoutAlien scout({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)});

    //
    float respawnTimer = 0.0f;
    bool alienActive = true;

    // Set the game to run at 60 FPS
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        player.update(deltaTime);

        // Check player collision with ScoutAlien
        if (alienActive) {
            scout.update(deltaTime, player.getPLPos());
            auto &projectiles = player.getProjectiles();
            for (auto it = projectiles.begin(); it != projectiles.end(); ++it) {
                if (CheckCollisionBoxes(it->getProjPos(), {10, 10})) {
                    alienActive = false;
                    respawnTimer = GetRandomValue(10, 20);
                    break;
                }
            }

            if (!scout.getBoolActive()) {
                alienActive = false;
                respawnTimer = GetRandomValue(10, 20);
            }
        } else {
            respawnTimer -= deltaTime;
            if (respawnTimer <= 0.0f) {
                scout.setEnemyPos({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)});
                scout.setEscapeMode(false);
                scout.setBoolActive(true);
                alienActive = true;
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw player and ScoutAlien
        player.draw();
        if (alienActive) {
            scout.draw();
        }

        // Player health display
        DrawText(TextFormat("Player Health: %i", player.getPLHealth()), 10, 10, 20, DARKGRAY);

        // respawn timer display
        if (!alienActive) { DrawText(TextFormat("ScoutAlien Respawn in: %.1f seconds", respawnTimer), 10, 30, 20, RED);}

        if (alienActive) {const char* modeText = scout.getEscapeMode() ? "Mode: Escape" : "Mode: Exploration";
            DrawText(modeText, 10, 50, 20, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
