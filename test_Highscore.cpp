#include <iostream>
#include <vector>
#include <algorithm>
#include "Highscore.h"
#include "raylib.h"
#include "raymath.h"
#include "Player.h"
#include "Asteroids.h"
#include <memory>
#include <ctime>

void ResetGame(Player &player, std::vector<std::unique_ptr<Asteroids>> &asteroids, int screenWidth, int screenHeight) {
    player = Player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);  // Reset player at center
    asteroids.clear();

    for (int i = 0; i < 6; i++) {
        auto newAsteroid = std::make_unique<Asteroids>(Vector2{0.0f, 0.0f}, Vector2{0.0f, 0.0f});
        newAsteroid->spawnAtEdge();
        newAsteroid->setSpeedTowards(player.getPLPos(), 150.0f);
        asteroids.push_back(std::move(newAsteroid));
    }
}

// Helper function to spawn additional asteroids
void SpawnAsteroids(std::vector<std::unique_ptr<Asteroids>>& asteroids, const Player& player, int numAsteroids) {
    for (int i = 0; i < numAsteroids; i++) {
        auto newAsteroid = std::make_unique<Asteroids>(Vector2{0.0f, 0.0f}, Vector2{0.0f, 0.0f});
        newAsteroid->spawnAtEdge();
        newAsteroid->setSpeedTowards(player.getPLPos(), 150.0f);
        asteroids.push_back(std::move(newAsteroid));
    }
}


int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Asteroids Improved");
    srand(static_cast<unsigned int>(time(0)));

    Player player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);
    std::vector<std::unique_ptr<Asteroids>> asteroids;
    asteroids.reserve(10);

    // Spawn initial asteroids
    ResetGame(player, asteroids, screenWidth, screenHeight);

    float timeAlive = 0.0f;
    bool gameOver = false;
    
    createFile(fileName);

    std::vector<Highscore> highscores;
    loadHighScores(highscores, fileName);

    bool showHighScoreMenu = false;
    bool hasntSaved = true;
    int bulletCollisionCounter = 0;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        if (gameOver && IsKeyPressed(KEY_R)) {
            ResetGame(player, asteroids, screenWidth, screenHeight);
            timeAlive = 0.0f;
            gameOver = false;
            hasntSaved = true;
            bulletCollisionCounter = 0;
            continue;
        }

        if (gameOver && IsKeyPressed(KEY_T) && hasntSaved) {
            if (!showHighScoreMenu) {
                Highscore newScore;
                newScore.score = static_cast<int>(timeAlive + 10 * bulletCollisionCounter);
                newScore.name = getPlayerName();
                saveHighScore(newScore, fileName); 
                highscores.push_back(newScore); 
                std::sort(highscores.begin(), highscores.end());
                showHighScoreMenu = true; // Set to true to show highscores
            } else {
                // If already showing highscores, toggle back
                showHighScoreMenu = false; 
                hasntSaved = false;
            }
        }


        if (!gameOver) {
            timeAlive += deltaTime;
            player.update(deltaTime);

            // Check for player death
            if (player.getPLHealth() <= 0) {
                gameOver = true;
            }

            Vector2 playerPos = player.getPLPos();
            int activeAsteroids = 0;

            // Update asteroids and handle collisions with projectiles
            for (size_t j = 0; j < asteroids.size();) {
                asteroids[j]->update(deltaTime, playerPos, 150.0f, player, asteroids);
                bool asteroidDestroyed = false;
                auto &projectiles = player.getProjectiles();
                for (auto it = projectiles.begin(); it != projectiles.end();) {
                    if (it->EnemyCollisionCheck(asteroids[j]->getEnemyPos(), asteroids[j]->getAsteroidsBounding())) {
                        asteroids[j]->setActive(false);
                        it = projectiles.erase(it);  // Remove the projectile
                        bulletCollisionCounter++;
                    } else {
                        ++it;
                    }

                    if (!asteroids[j]->isActive()) {
                        asteroids[j]->breakApart(asteroids);
                        asteroids.erase(asteroids.begin() + j);
                        asteroidDestroyed = true;
                        break;
                    }
                }

                if (!asteroidDestroyed) {
                    if (asteroids[j]->isActive()) {
                        activeAsteroids++;
                    }
                    ++j;
                }
            }

            // Update projectiles and remove off-screen ones
            auto &projectiles = player.getProjectiles();
            for (auto it = projectiles.begin(); it != projectiles.end();) {
                it->update(deltaTime);
                Vector2 projPos = it->getProjPos();
                if (projPos.x < 0 || projPos.x > screenWidth || projPos.y < 0 || projPos.y > screenHeight || !it->isActive()) {
                    player.decrementBulletCount();
                    it = projectiles.erase(it);
                } else {
                    ++it;
                }
            }

            // Check if all asteroids are destroyed and spawn new ones if needed
            if (activeAsteroids == 0) {
                SpawnAsteroids(asteroids, player, 5);  // Spawn 5 new asteroids
            }

            // Drawing
            BeginDrawing();
            ClearBackground(RAYWHITE);

            player.draw();
            for (const auto &asteroid : asteroids) {
                asteroid->draw();
            }

            DrawText(TextFormat("Player Health: %i", player.getPLHealth()), 10, 10, 20, DARKGRAY);
            DrawText(TextFormat("Active Bullets: %d", player.getActiveBulletCount()), 10, 30, 20, DARKGRAY);
            DrawText(TextFormat("Active Asteroids: %d", activeAsteroids), 10, 50, 20, DARKGRAY);
            DrawText(TextFormat("Time Alive: %.1f seconds", timeAlive), 10, 90, 20, DARKGRAY);

            EndDrawing();
        } else {
            if (showHighScoreMenu) {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("HIGH SCORES", screenWidth / 2 - 100, screenHeight / 2 - 50, 40, DARKGRAY);
                displayHighScores(highscores); // Show the list of highscores
                DrawText("Press [T] to go back to Game Over screen", screenWidth / 2 - 200, screenHeight / 2 + 100, 20, DARKGRAY);
                EndDrawing();
            } else{
            // Game Over screen
                BeginDrawing();
                ClearBackground(RAYWHITE);

                DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 50, 40, RED);
                DrawText(TextFormat("Time Alive: %.2f seconds", timeAlive), screenWidth / 2 - 120, screenHeight / 2, 20, DARKGRAY);
                DrawText("Press [R] to restart, or [ESC] to quit", screenWidth / 2 - 150, screenHeight / 2 + 40, 20, DARKGRAY);
                DrawText("Press [T] to save your highscore", screenWidth / 2 - 200, screenHeight / 2 + 80, 20, DARKGRAY);
                DrawText(TextFormat("FPS: %i", GetFPS()), 10, 130, 20, DARKGRAY);

                EndDrawing();
            }
        }
    }
}