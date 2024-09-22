#include "raylib.h"
#include "raymath.h"
#include "Player.h"
#include "Asteroids.h"
#include <vector>
#include <memory>
#include <ctime>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Asteroids Test");
    srand(static_cast<unsigned int>(time(0)));

    Player player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);
    std::vector<std::unique_ptr<Asteroids>> asteroids;
    asteroids.reserve(10);

    // Spawn initial asteroids
    for (int i = 0; i < 6; i++) {
        auto newAsteroid = std::make_unique<Asteroids>(Vector2{0.0f, 0.0f}, Vector2{0.0f, 0.0f});
        newAsteroid->spawnAtEdge();
        newAsteroid->setSpeedTowards(player.getPLPos(), 150.0f);
        asteroids.push_back(std::move(newAsteroid));
    }

    float timeAlive = 0.0f;
    bool gameOver = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Input handling, even if the game is over
        if (gameOver && IsKeyPressed(KEY_R)) {
            // Reset player and asteroids
            player = Player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);
            asteroids.clear();
            for (int i = 0; i < 6; i++) {
                auto newAsteroid = std::make_unique<Asteroids>(Vector2{0.0f, 0.0f}, Vector2{0.0f, 0.0f});
                newAsteroid->spawnAtEdge();
                newAsteroid->setSpeedTowards(player.getPLPos(), 150.0f);
                asteroids.push_back(std::move(newAsteroid));
            }
            timeAlive = 0.0f;
            gameOver = false;
            continue;  // Restart the game loop immediately after reset
        }

        if (!gameOver) {
            // Update time alive only when game is running
            timeAlive += deltaTime;

            // Update player
            player.update(deltaTime);

            // Check if the player is dead
            if (player.getPLHealth() <= 0) {
                gameOver = true;
            }

            Vector2 playerPos = player.getPLPos();
            int activeAsteroids = 0; // Track active asteroids

            // Update asteroids
            for (size_t j = 0; j < asteroids.size(); ) {
                bool asteroidDestroyed = false;
                asteroids[j]->update(deltaTime, playerPos, 150.0f, player, asteroids);

                // Check for collisions with projectiles
                auto& projectiles = player.getProjectiles();
                for (auto it = projectiles.begin(); it != projectiles.end(); ) {
                    if (it->EnemyCollisionCheck(asteroids[j]->getEnemyPos(), asteroids[j]->getAsteroidsBounding())) {
                        asteroids[j]->setActive(false);

                        // Check if the asteroid is destroyed
                        if (!asteroids[j]->isActive()) {
                            asteroids[j]->breakApart(asteroids);
                            asteroids.erase(asteroids.begin() + j);
                            asteroidDestroyed = true;
                            break;
                        }

                        it = projectiles.erase(it);
                    } else {
                        ++it;
                    }
                }

                if (!asteroidDestroyed) {
                    if (asteroids[j]->isActive()) {
                        activeAsteroids++;
                    }
                    ++j;
                }
            }

            // Update projectiles and check for off-screen
            auto& projectiles = player.getProjectiles();
            for (auto it = projectiles.begin(); it != projectiles.end(); ) {
                it->update(deltaTime);
                Vector2 projPos = it->getProjPos();
                bool isOffScreen = projPos.x < 0 || projPos.x > screenWidth || projPos.y < 0 || projPos.y > screenHeight;

                if (isOffScreen || !it->isActive()) {
                    player.decrementBulletCount();
                    it = projectiles.erase(it);
                } else {
                    ++it;
                }
            }

            // Track active projectiles
            int activeProjectiles = projectiles.size();

            // Total active objects
            int totalActive = activeAsteroids + activeProjectiles;

            // Drawing
            BeginDrawing();
            ClearBackground(RAYWHITE);

            if (!gameOver) {
                player.draw();
                for (const auto& asteroid : asteroids) {
                    asteroid->draw();
                }
                DrawText(TextFormat("Player Health: %i", player.getPLHealth()), 10, 10, 20, DARKGRAY);
                DrawText(TextFormat("Active Bullets: %d", player.getActiveBulletCount()), 10, 30, 20, DARKGRAY);
                DrawText(TextFormat("Active Asteroids: %d", activeAsteroids), 10, 50, 20, DARKGRAY);
                DrawText(TextFormat("Total Active: %d", totalActive), 10, 90, 20, DARKGRAY);
                DrawText(TextFormat("Time Alive: %.1f seconds", timeAlive), 10, 110, 20, DARKGRAY);
            } else {
                DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 50, 40, RED);
                DrawText(TextFormat("Time Alive: %.2f seconds", timeAlive), screenWidth / 2 - 120, screenHeight / 2, 20, DARKGRAY);
                DrawText("Press [R] to restart or [ESC] to quit", screenWidth / 2 - 150, screenHeight / 2 + 40, 20, DARKGRAY);
            }

            DrawText(TextFormat("FPS: %i", GetFPS()), 10, 130, 20, DARKGRAY);
            EndDrawing();
        } else {
            // Draw Game Over screen if gameOver == true
            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 50, 40, RED);
            DrawText(TextFormat("Time Alive: %.2f seconds", timeAlive), screenWidth / 2 - 120, screenHeight / 2, 20, DARKGRAY);
            DrawText("Press [R] to restart or [ESC] to quit", screenWidth / 2 - 150, screenHeight / 2 + 40, 20, DARKGRAY);
            DrawText(TextFormat("FPS: %i", GetFPS()), 10, 130, 20, DARKGRAY);

            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}
