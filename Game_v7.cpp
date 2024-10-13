#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <ctime>
#include <fstream>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "Highscore.h"
#include "Player.h"
#include "Asteroids.h"
#include "ScoutAlien.h"

const char* PLAYER_STATE_FILE = "player_state.txt";

// Function to save the game state
void SaveGameState(const Player& player, float timeAlive) {
    std::ofstream file(PLAYER_STATE_FILE);
    if (file.is_open()) {
        file << player.getPLPos().x << " " << player.getPLPos().y << " "
             << player.getPLHealth() << " " << timeAlive;
        file.close();
    }
}

// Function to load the game state
bool LoadGameState(Player& player, float& timeAlive) {
    std::ifstream file(PLAYER_STATE_FILE);
    if (file.is_open()) {
        Vector2 position;
        int health;
        file >> position.x >> position.y >> health >> timeAlive;
        player = Player(position, health);
        file.close();
        return true;
    }
    return false;
}

// Function to delete the saved game state
void DeleteGameState() {
    std::remove(PLAYER_STATE_FILE);
}

// Function to reset the game state
void ResetGame(Player &player, std::vector<std::unique_ptr<Asteroids>> &asteroids, ScoutAlien &scout, int screenWidth, int screenHeight) {
    player = Player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);
    asteroids.clear();

    for (int i = 0; i < 6; i++) {
        auto newAsteroid = std::make_unique<Asteroids>(Vector2{0.0f, 0.0f}, Vector2{0.0f, 0.0f});
        newAsteroid->spawnAtEdge();
        newAsteroid->setSpeedTowards(player.getPLPos(), 150.0f);
        asteroids.push_back(std::move(newAsteroid));
    }

    scout.setEnemyPos({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)});
    scout.setEscapeMode(false);
    scout.setBoolActive(true);
}

// Function to spawn asteroids
void SpawnAsteroids(std::vector<std::unique_ptr<Asteroids>>& asteroids, const Player& player, int numAsteroids) {
    for (int i = 0; i < numAsteroids; i++) {
        auto newAsteroid = std::make_unique<Asteroids>(Vector2{0.0f, 0.0f}, Vector2{0.0f, 0.0f});
        newAsteroid->spawnAtEdge();
        newAsteroid->setSpeedTowards(player.getPLPos(), 150.0f);
        asteroids.push_back(std::move(newAsteroid));
    }
}

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Asteroids Game v7");
    SetTargetFPS(60);
    
    srand(static_cast<unsigned int>(time(0)));

    Player player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);
    std::vector<std::unique_ptr<Asteroids>> asteroids;
    asteroids.reserve(10);
    ScoutAlien scout({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)});

    float timeAlive = 0.0f;
    bool gameOver = false;
    float scoutRespawnTimer = 0.0f;
    bool scoutActive = true;
    
    const char* fileName = "highscores.txt";
    createFile(fileName);

    std::vector<Highscore> highscores;
    loadHighScores(highscores, fileName);

    bool showHighScoreMenu = false;
    bool hasntSaved = true;

    // Try to load the game state
    if (LoadGameState(player, timeAlive)) {
        // If loading successful, only reset asteroids and scout
        asteroids.clear();
        SpawnAsteroids(asteroids, player, 6);
        scout.setEnemyPos({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)});
        scout.setEscapeMode(false);
        scout.setBoolActive(true);
    } else {
        // If loading fails, reset the entire game
        ResetGame(player, asteroids, scout, screenWidth, screenHeight);
    }

    // Main game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Handle game over state
        if (gameOver && IsKeyPressed(KEY_R)) {
            ResetGame(player, asteroids, scout, screenWidth, screenHeight);
            timeAlive = 0.0f;
            gameOver = false;
            scoutActive = true;
            DeleteGameState(); // Delete the saved game state when restarting
            continue;
        }

        if (gameOver && IsKeyPressed(KEY_T) && hasntSaved) {
            if (!showHighScoreMenu) {
                Highscore newScore;
                newScore.score = static_cast<int>(timeAlive * 100);
                newScore.name = getPlayerName();
                saveHighScore(newScore, fileName); 
                highscores.push_back(newScore); 
                std::sort(highscores.begin(), highscores.end());
                showHighScoreMenu = true;
            } else {
                showHighScoreMenu = false; 
                hasntSaved = false;
            }
        }

        // Update game state if not game over
        if (!gameOver) {
            timeAlive += deltaTime;
            player.update(deltaTime);

            if (player.getPLHealth() <= 0) {
                gameOver = true;
                DeleteGameState(); // Delete the saved game state when game over
            }

            Vector2 playerPos = player.getPLPos();
            int activeAsteroids = 0;

            // Update asteroids
            for (size_t j = 0; j < asteroids.size();) {
                asteroids[j]->update(deltaTime, playerPos, 150.0f, player, asteroids);

                bool asteroidDestroyed = false;
                auto &projectiles = player.getProjectiles();
                for (auto it = projectiles.begin(); it != projectiles.end();) {
                    if ((*it)->EnemyCollisionCheck(asteroids[j]->getEnemyPos(), asteroids[j]->getAsteroidsBounding())) {
                        asteroids[j]->setActive(false);
                        it = projectiles.erase(it);
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

            // Update Scout Alien
            if (scoutActive) {
                scout.update(deltaTime, playerPos);
                auto &projectiles = player.getProjectiles();
                for (auto it = projectiles.begin(); it != projectiles.end(); ++it) {
                    if (scout.checkCollisionBox((*it)->getProjPos(), {10, 10})) { // Dereference with (*it)
                        scoutActive = false;
                        scoutRespawnTimer = GetRandomValue(10, 20);
                        break;
                    }
                }

                if (!scout.getBoolActive()) {
                    scoutActive = false;
                    scoutRespawnTimer = GetRandomValue(10, 20);
                }
            } else {
                scoutRespawnTimer -= deltaTime;
                if (scoutRespawnTimer <= 0.0f) {
                    scout.setEnemyPos({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)});
                    scout.setEscapeMode(false);
                    scout.setBoolActive(true);
                    scoutActive = true;
                }
            }

            // Update projectiles
            auto &projectiles = player.getProjectiles();
            for (auto it = projectiles.begin(); it != projectiles.end();) {
                (*it)->update(deltaTime); // Dereference to call update
                Vector2 projPos = (*it)->getProjPos(); // Dereference to access getProjPos
                if (projPos.x < 0 || projPos.x > screenWidth || projPos.y < 0 || projPos.y > screenHeight || !(*it)->isActive()) {
                    player.decrementBulletCount();
                    it = projectiles.erase(it);
                } else {
                    ++it;
                }
            }

            // Spawn new asteroids if needed
            if (activeAsteroids == 0) {
                SpawnAsteroids(asteroids, player, 5);
            }

            // Save game state periodically (e.g., every 5 seconds)
            static float saveTimer = 0.0f;
            saveTimer += deltaTime;
            if (saveTimer >= 5.0f) {
                SaveGameState(player, timeAlive);
                saveTimer = 0.0f;
            }

            // Drawing
            BeginDrawing();
            ClearBackground(RAYWHITE);

            player.draw();
            for (const auto &asteroid : asteroids) {
                asteroid->draw();
            }
            if (scoutActive) {
                scout.draw();
            }

            DrawText(TextFormat("Player Health: %i", player.getPLHealth()), 10, 10, 20, DARKGRAY);
            DrawText(TextFormat("Active Bullets: %d", player.getActiveBulletCount()), 10, 30, 20, DARKGRAY);
            DrawText(TextFormat("Active Asteroids: %d", activeAsteroids), 10, 50, 20, DARKGRAY);
            DrawText(TextFormat("Time Alive: %.1f seconds", timeAlive), 10, 70, 20, DARKGRAY);
            
            if (scoutActive) {
                const char* modeText = scout.getEscapeMode() ? "Scout Mode: Escape" : "Scout Mode: Exploration";
                DrawText(modeText, 10, 90, 20, BLUE);
            } else {
                DrawText(TextFormat("Scout Respawn in: %.1f seconds", scoutRespawnTimer), 10, 90, 20, RED);
            }

            EndDrawing();
        } else {
            // Handle game over screen
            if (showHighScoreMenu) {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("HIGH SCORES", screenWidth / 2 - 100, screenHeight / 2 - 50, 40, DARKGRAY);
                displayHighScores(highscores);
                DrawText("Press [T] to go back to Game Over screen", screenWidth / 2 - 200, screenHeight / 2 + 100, 20, DARKGRAY);
                EndDrawing();
            } else {
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

    // Cleanup
    CloseWindow();
    return 0;
}