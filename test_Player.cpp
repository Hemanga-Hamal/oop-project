#include <iostream>
#include <cassert>
#include <string>
#include "raylib.h"
#include "math.h"
#include "Player.h"

// Struct to store test results
struct TestResult {
    std::string testName;
    bool passed;
};

// Function to draw test results on screen
void drawTestResults(const TestResult results[], int count) {
    int yPosition = 20;  // Starting Y position for drawing text

    for (int i = 0; i < count; i++) {
        std::string message = results[i].testName + ": " + (results[i].passed ? "PASSED" : "FAILED");
        Color textColor = results[i].passed ? GREEN : RED;
        DrawText(message.c_str(), 20, yPosition, 20, textColor);
        yPosition += 30;  // Move down for the next result
    }
}

// Test functions
bool testPlayerInitialization() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    return player.getPLPos().x == initialPos.x &&
           player.getPLPos().y == initialPos.y &&
           player.getPLHealth() == initialHealth;
}

bool testPlayerMovement() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    player.setPLSpeed({10.0f, 0.0f});
    player.movement(1.0f);
    player.setPLSpeed({-10.0f, 0.0f});
    player.movement(1.0f);

    return player.getPLPos().x == 0.0f && player.getPLPos().y == 0.0f;
}

bool testPlayerShoot() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    player.shoot();
    return player.getActiveBulletCount() == 1;
}

bool testPlayerTakeDamage() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    player.takeDamage(10);
    return player.getPLHealth() == 90;
}

bool testPlayerCollision() {
    Vector2 playerPos = {0.0f, 0.0f};
    int playerHealth = 100;
    Player player(playerPos, playerHealth);

    Vector2 enemyPos = {5.0f, 5.0f};
    Vector2 enemyBounding = {10.0f, 10.0f};

    return player.checkColEnemy(enemyPos, enemyBounding);
}

bool testPlayerRotation() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    Vector2 mousePos = {10.0f, 0.0f};
    player.updateRotation(mousePos);

    return player.getRotation() == atan2f(0.0f, 10.0f) + (float)PI / 2.0f;
}

// Main function
int main() {
    // Initialize Raylib window
    InitWindow(800, 600, "Player Test Results");
    SetTargetFPS(60);

    // Run the tests and store the results
    TestResult results[] = {
        {"Player Initialization", testPlayerInitialization()},
        {"Player Movement", testPlayerMovement()},
        {"Player Shoot", testPlayerShoot()},
        {"Player Take Damage", testPlayerTakeDamage()},
        {"Player Collision", testPlayerCollision()},
        {"Player Rotation", testPlayerRotation()}
    };
    int testCount = sizeof(results) / sizeof(results[0]);

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the test results
        drawTestResults(results, testCount);

        EndDrawing();
    }

    // Close Raylib window
    CloseWindow();

    return 0;
}
