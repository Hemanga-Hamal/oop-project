// test_PlayerProj.cpp
#include <iostream>
#include <cassert>
#include "PlayerProj.h"
#include "raylib.h"

// Struct to store test results
struct TestResult {
    std::string testName;
    bool passed;
};

// Function to draw test results on the screen
void drawTestResults(const TestResult results[], int count) {
    int yPosition = 20; // Starting Y position for drawing text
    for (int i = 0; i < count; i++) {
        std::string message = results[i].testName + ": " + (results[i].passed ? "PASSED" : "FAILED");
        Color textColor = results[i].passed ? GREEN : RED;
        DrawText(message.c_str(), 20, yPosition, 20, textColor);
        yPosition += 30; // Move down for the next result
    }
}

// Helper function to initialize the test environment
void initTestEnvironment() {
    InitWindow(800, 600, "Player Projectile Test Results");
    SetTargetFPS(60);
}

// Helper function to cleanup the test environment
void cleanupTestEnvironment() {
    CloseWindow();
}

// Test functions remain the same but return results
bool testPlayerProjInitialization() {
    Vector2 pos = {0.0f, 0.0f};
    Vector2 speed = {1.0f, 1.0f};
    PlayerProj proj(pos, speed);

    bool result = (proj.isActive() == true);
    std::cout << "testPlayerProjInitialization " << (result ? "passed!" : "failed!") << std::endl;
    return result;
}

bool testPlayerProjSetters() {
    Vector2 pos = {0.0f, 0.0f};
    Vector2 speed = {1.0f, 1.0f};
    PlayerProj proj(pos, speed);

    Vector2 newPos = {10.0f, 10.0f};
    Vector2 newSpeed = {2.0f, 2.0f};
    int newDamage = 20;

    proj.setProjPos(newPos);
    proj.setProjSpeed(newSpeed);
    proj.setProjDamage(newDamage);

    bool result = (proj.getProjPos().x == newPos.x && proj.getProjPos().y == newPos.y &&
                   proj.getProjSpeed().x == newSpeed.x && proj.getProjSpeed().y == newSpeed.y &&
                   proj.getProjDamage() == newDamage);

    std::cout << "testPlayerProjSetters " << (result ? "passed!" : "failed!") << std::endl;
    return result;
}

bool testPlayerProjEdgeCollision() {
    Vector2 pos = {0.0f, 0.0f};
    Vector2 speed = {1.0f, 1.0f};
    PlayerProj proj(pos, speed);

    proj.setProjPos({-1.0f, 0.0f});
    bool result1 = proj.checkEdgeCollision();

    proj.setProjPos({GetScreenWidth() + 1.0f, 0.0f});
    bool result2 = proj.checkEdgeCollision();

    proj.setProjPos({0.0f, -1.0f});
    bool result3 = proj.checkEdgeCollision();

    proj.setProjPos({0.0f, GetScreenHeight() + 1.0f});
    bool result4 = proj.checkEdgeCollision();

    bool result = result1 && result2 && result3 && result4;

    std::cout << "testPlayerProjEdgeCollision " << (result ? "passed!" : "failed!") << std::endl;
    return result;
}

bool testPlayerProjEnemyCollision() {
    Vector2 pos = {0.0f, 0.0f};
    Vector2 speed = {1.0f, 1.0f};
    PlayerProj proj(pos, speed);

    Vector2 enemyPos = {5.0f, 5.0f};
    Vector2 enemyBounding = {10.0f, 10.0f};

    proj.setProjPos({5.0f, 5.0f});
    bool result1 = proj.EnemyCollisionCheck(enemyPos, enemyBounding);

    proj.setProjPos({15.0f, 15.0f});
    bool result2 = proj.EnemyCollisionCheck(enemyPos, enemyBounding);

    bool result = result1 && !result2;

    std::cout << "testPlayerProjEnemyCollision " << (result ? "passed!" : "failed!") << std::endl;
    return result;
}

int main() {
    initTestEnvironment();

    // Run the tests and store the results
    TestResult results[] = {
        {"Test PlayerProj Initialization", testPlayerProjInitialization()},
        {"Test PlayerProj Setters", testPlayerProjSetters()},
        {"Test PlayerProj Edge Collision", testPlayerProjEdgeCollision()},
        {"Test PlayerProj Enemy Collision", testPlayerProjEnemyCollision()}
    };
    int testCount = sizeof(results) / sizeof(results[0]);

    // Main game loop to display results
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the test results
        drawTestResults(results, testCount);

        EndDrawing();
    }

    cleanupTestEnvironment();
    return 0;
}
