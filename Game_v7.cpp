#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "Highscore.h"
#include "Player.h"
#include "Asteroids.h"
#include "ScoutAlien.h"

const char *PLAYER_STATE_FILE = "player_state.txt";

// Function to save the game state
void SaveGameState(const Player &player, float timeAlive)
{
    std::ofstream file(PLAYER_STATE_FILE);
    if (file.is_open())
    {
        file << player.getPLPos().x << " " << player.getPLPos().y << " "
             << player.getPLHealth() << " " << timeAlive;
        file.close();
    }
}

// Function to load the game state
bool LoadGameState(Player &player, float &timeAlive)
{
    std::ifstream file(PLAYER_STATE_FILE);
    if (file.is_open())
    {
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
void DeleteGameState()
{
    std::remove(PLAYER_STATE_FILE);
}

// Function to reset the game state
void ResetGame(Player &player, std::vector<std::unique_ptr<Asteroids>> &asteroids, ScoutAlien &scout, int screenWidth, int screenHeight)
{
    player = Player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);
    asteroids.clear();

    for (int i = 0; i < 6; i++)
    {
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
void SpawnAsteroids(std::vector<std::unique_ptr<Asteroids>> &asteroids, const Player &player, int numAsteroids)
{
    for (int i = 0; i < numAsteroids; i++)
    {
        auto newAsteroid = std::make_unique<Asteroids>(Vector2{0.0f, 0.0f}, Vector2{0.0f, 0.0f});
        newAsteroid->spawnAtEdge();
        newAsteroid->setSpeedTowards(player.getPLPos(), 150.0f);
        asteroids.push_back(std::move(newAsteroid));
    }
}

struct MenuAsteroid {
    Vector2 position;
    Vector2 velocity;
    float radius;
};

bool HandleMainMenu(int screenWidth, int screenHeight)
{
    const int buttonWidth = 200;
    const int buttonHeight = 50;
    const int buttonSpacing = 20;
    const int startY = screenHeight / 2 - (3 * buttonHeight + 2 * buttonSpacing) / 2;

    Rectangle playButton = {
        screenWidth / 2.0f - static_cast<float>(buttonWidth) / 2,
        static_cast<float>(startY),
        static_cast<float>(buttonWidth),
        static_cast<float>(buttonHeight)};

    Rectangle instructionsButton = {
        screenWidth / 2.0f - static_cast<float>(buttonWidth) / 2,
        static_cast<float>(startY + buttonHeight + buttonSpacing),
        static_cast<float>(buttonWidth),
        static_cast<float>(buttonHeight)};

    Rectangle quitButton = {
        screenWidth / 2.0f - static_cast<float>(buttonWidth) / 2,
        static_cast<float>(startY + 2 * buttonHeight + 2 * buttonSpacing),
        static_cast<float>(buttonWidth),
        static_cast<float>(buttonHeight)};

    bool showInstructions = false;

    // Initialize background asteroids
    std::vector<MenuAsteroid> asteroids;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> xDist(0, screenWidth);
    std::uniform_real_distribution<> yDist(0, screenHeight);
    std::uniform_real_distribution<> velDist(-100, 100);
    std::uniform_real_distribution<> radiusDist(5, 20);

    for (int i = 0; i < 20; ++i) {
        asteroids.push_back({
            {static_cast<float>(xDist(gen)), static_cast<float>(yDist(gen))},
            {static_cast<float>(velDist(gen)), static_cast<float>(velDist(gen))},
            static_cast<float>(radiusDist(gen))
        });
    }

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // Update asteroid positions
        for (auto& asteroid : asteroids) {
            asteroid.position.x += asteroid.velocity.x * deltaTime;
            asteroid.position.y += asteroid.velocity.y * deltaTime;

            // Wrap around screen edges
            if (asteroid.position.x < -asteroid.radius) asteroid.position.x = screenWidth + asteroid.radius;
            if (asteroid.position.x > screenWidth + asteroid.radius) asteroid.position.x = -asteroid.radius;
            if (asteroid.position.y < -asteroid.radius) asteroid.position.y = screenHeight + asteroid.radius;
            if (asteroid.position.y > screenHeight + asteroid.radius) asteroid.position.y = -asteroid.radius;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw background asteroids
        for (const auto& asteroid : asteroids) {
            DrawCircleV(asteroid.position, asteroid.radius, LIGHTGRAY);
        }

        if (!showInstructions)
        {
            const char *title = "ASTEROIDS ON A BUDGET";
            DrawText(title, screenWidth / 2 - MeasureText(title, 50) / 2, 100, 50, DARKGRAY);

            // Draw buttons
            DrawRectangleRec(playButton, LIGHTGRAY);
            DrawRectangleRec(instructionsButton, LIGHTGRAY);
            DrawRectangleRec(quitButton, LIGHTGRAY);

            const char *playText = "PLAY";
            DrawText(playText, playButton.x + buttonWidth / 2 - MeasureText(playText, 20) / 2, playButton.y + buttonHeight / 2 - 10, 20, DARKGRAY);

            const char *instructionsText = "INSTRUCTIONS";
            DrawText(instructionsText, instructionsButton.x + buttonWidth / 2 - MeasureText(instructionsText, 20) / 2, instructionsButton.y + buttonHeight / 2 - 10, 20, DARKGRAY);

            const char *quitText = "QUIT";
            DrawText(quitText, quitButton.x + buttonWidth / 2 - MeasureText(quitText, 20) / 2, quitButton.y + buttonHeight / 2 - 10, 20, DARKGRAY);

            // Check button clicks
            if (CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(GetMousePosition(), instructionsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                showInstructions = true;
            }
            if (CheckCollisionPointRec(GetMousePosition(), quitButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                EndDrawing();
                return false;
            }
        }
        else
        {
            // Display instructions
            const char *instructionsTitle = "INSTRUCTIONS";
            DrawText(instructionsTitle, screenWidth / 2 - MeasureText(instructionsTitle, 40) / 2, 100, 40, DARKGRAY);

            const char *moveInstructions = "Use W,A,S,D keys to move and avoid collisions";
            DrawText(moveInstructions, screenWidth / 2 - MeasureText(moveInstructions, 20) / 2, 200, 20, DARKGRAY);

            const char *shootInstructions = "Press SPACE to shoot to Destroy asteroids and Aliens";
            DrawText(shootInstructions, screenWidth / 2 - MeasureText(shootInstructions, 20) / 2, 230, 20, DARKGRAY);

            const char *funText = "ESE key to close the game";
            DrawText(funText, screenWidth / 2 - MeasureText(funText, 20) / 2, 260, 20, DARKGRAY);

            const char *escapeText = "Press Q to return to menu";
            DrawText(escapeText, screenWidth / 2 - MeasureText(escapeText, 20) / 2, screenHeight - 50, 20, DARKGRAY);

            if (IsKeyPressed(KEY_Q))
            {
                showInstructions = false;
            }
        }

        EndDrawing();
    }

    return false;
}

int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "ASTEROIDS ON A BUDGET");
    SetTargetFPS(60);

    srand(static_cast<unsigned int>(time(0)));

    // Main menu loop
    if (!HandleMainMenu(screenWidth, screenHeight))
    {
        CloseWindow();
        return 0;
    }

    Player player({screenWidth / 2.0f, screenHeight / 2.0f}, 100);
    std::vector<std::unique_ptr<Asteroids>> asteroids;
    asteroids.reserve(10);
    ScoutAlien scout({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)});

    float timeAlive = 0.0f;
    bool gameOver = false;
    float scoutRespawnTimer = 0.0f;
    bool scoutActive = true;

    const char *fileName = "highscores.txt";
    createFile(fileName);

    std::vector<Highscore> highscores;
    loadHighScores(highscores, fileName);

    bool showHighScoreMenu = false;
    bool hasntSaved = true;

    // Try to load the game state
    if (LoadGameState(player, timeAlive))
    {
        // If loading successful, only reset asteroids and scout
        asteroids.clear();
        SpawnAsteroids(asteroids, player, 6);
        scout.setEnemyPos({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)});
        scout.setEscapeMode(false);
        scout.setBoolActive(true);
    }
    else
    {
        // If loading fails, reset the entire game
        ResetGame(player, asteroids, scout, screenWidth, screenHeight);
    }

    // Main game loop
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        // Handle game over state
        if (gameOver && IsKeyPressed(KEY_R))
        {
            ResetGame(player, asteroids, scout, screenWidth, screenHeight);
            timeAlive = 0.0f;
            gameOver = false;
            scoutActive = true;
            hasntSaved = true;
            DeleteGameState();
            continue;
        }

        if (gameOver && IsKeyPressed(KEY_T) && hasntSaved)
        {
            if (!showHighScoreMenu)
            {
                Highscore newScore;
                newScore.score = static_cast<int>(timeAlive * 100);
                newScore.name = getPlayerName();
                saveHighScore(newScore, fileName);
                highscores.push_back(newScore);
                std::sort(highscores.begin(), highscores.end());
                showHighScoreMenu = true;
            }
            else
            {
                showHighScoreMenu = false;
                hasntSaved = false;
            }
        }

        // Update game state if not game over
        if (!gameOver)
        {
            timeAlive += deltaTime;
            player.update(deltaTime);

            if (player.getPLHealth() <= 0)
            {
                gameOver = true;
                DeleteGameState();
            }

            Vector2 playerPos = player.getPLPos();
            int activeAsteroids = 0;

            // Update asteroids
            for (size_t j = 0; j < asteroids.size();)
            {
                asteroids[j]->update(deltaTime, playerPos, 150.0f, player, asteroids);

                bool asteroidDestroyed = false;
                auto &projectiles = player.getProjectiles();
                for (auto it = projectiles.begin(); it != projectiles.end();)
                {
                    if ((*it)->EnemyCollisionCheck(asteroids[j]->getEnemyPos(), asteroids[j]->getAsteroidsBounding()))
                    {
                        asteroids[j]->setActive(false);
                        it = projectiles.erase(it);
                    }
                    else
                    {
                        ++it;
                    }

                    if (!asteroids[j]->isActive())
                    {
                        asteroids[j]->breakApart(asteroids);
                        asteroids.erase(asteroids.begin() + j);
                        asteroidDestroyed = true;
                        break;
                    }
                }

                if (!asteroidDestroyed)
                {
                    if (asteroids[j]->isActive())
                    {
                        activeAsteroids++;
                    }
                    ++j;
                }
            }

            // Update Scout Alien
            if (scoutActive)
            {
                scout.update(deltaTime, playerPos);
                auto &projectiles = player.getProjectiles();
                for (auto it = projectiles.begin(); it != projectiles.end(); ++it)
                {
                    if (scout.checkCollisionBox((*it)->getProjPos(), {10, 10}))
                    {
                        scoutActive = false;
                        scoutRespawnTimer = GetRandomValue(10, 20);
                        break;
                    }
                }

                if (!scout.getBoolActive())
                {
                    scoutActive = false;
                    scoutRespawnTimer = GetRandomValue(10, 20);
                }
            }
            else
            {
                scoutRespawnTimer -= deltaTime;
                if (scoutRespawnTimer <= 0.0f)
                {
                    scout.setEnemyPos({(float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight)});
                    scout.setEscapeMode(false);
                    scout.setBoolActive(true);
                    scoutActive = true;
                }
            }

            // Update projectiles
            auto &projectiles = player.getProjectiles();
            for (auto it = projectiles.begin(); it != projectiles.end();)
            {
                (*it)->update(deltaTime);
                Vector2 projPos = (*it)->getProjPos();
                if (projPos.x < 0 || projPos.x > screenWidth || projPos.y < 0 || projPos.y > screenHeight || !(*it)->isActive())
                {
                    player.decrementBulletCount();
                    it = projectiles.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            // Spawn new asteroids if needed
            if (activeAsteroids == 0)
            {
                SpawnAsteroids(asteroids, player, 5);
            }

            // Save game state periodically (e.g., every 5 seconds)
            static float saveTimer = 0.0f;
            saveTimer += deltaTime;
            if (saveTimer >= 5.0f)
            {
                SaveGameState(player, timeAlive);
                saveTimer = 0.0f;
            }

            // Drawing
            BeginDrawing();
            ClearBackground(RAYWHITE);

            player.draw();
            for (const auto &asteroid : asteroids)
            {
                asteroid->draw();
            }
            if (scoutActive)
            {
                scout.draw();
            }

            const char *healthText = TextFormat("Player Health: %i", player.getPLHealth());
            DrawText(healthText, screenWidth / 2 - MeasureText(healthText, 20) / 2, 10, 20, DARKGRAY);

            const char *timeText = TextFormat("Time Alive: %.1f seconds", timeAlive);
            DrawText(timeText, screenWidth / 2 - MeasureText(timeText, 20) / 2, 40, 20, DARKGRAY);

            EndDrawing();
        }
        else
        {
            // Handle game over screen
            if (gameOver)
            {
                if (showHighScoreMenu)
                {
                    BeginDrawing();
                    ClearBackground(RAYWHITE);

                    const char *highScoresTitle = "HIGH SCORES";
                    DrawText(highScoresTitle, screenWidth / 2 - MeasureText(highScoresTitle, 40) / 2, screenHeight / 2 - 50, 40, DARKGRAY);

                    displayHighScores(highscores);

                    const char *backText = "Press [T] to go back to Game Over screen";
                    DrawText(backText, screenWidth / 2 - MeasureText(backText, 20) / 2, screenHeight / 2 + 100, 20, DARKGRAY);

                    EndDrawing();
                }
                else
                {
                    BeginDrawing();
                    ClearBackground(RAYWHITE);

                    const char *gameOverText = "GAME OVER";
                    DrawText(gameOverText, screenWidth / 2 - MeasureText(gameOverText, 40) / 2, screenHeight / 2 - 50, 40, RED);

                    const char *finalTimeText = TextFormat("Time Alive: %.2f seconds", timeAlive);
                    DrawText(finalTimeText, screenWidth / 2 - MeasureText(finalTimeText, 20) / 2, screenHeight / 2, 20, DARKGRAY);

                    const char *restartText = "Press [R] to restart, or [ESC] to quit";
                    DrawText(restartText, screenWidth / 2 - MeasureText(restartText, 20) / 2, screenHeight / 2 + 40, 20, DARKGRAY);

                    const char *saveScoreText = "Press [T] to save your highscore";
                    DrawText(saveScoreText, screenWidth / 2 - MeasureText(saveScoreText, 20) / 2, screenHeight / 2 + 80, 20, DARKGRAY);

                    const char *fpsText = TextFormat("FPS: %i", GetFPS());
                    DrawText(fpsText, screenWidth / 2 - MeasureText(fpsText, 20) / 2, screenHeight - 30, 20, DARKGRAY);

                    EndDrawing();
                }
            }
        }
    }

    // Cleanup
    CloseWindow();
    return 0;
}