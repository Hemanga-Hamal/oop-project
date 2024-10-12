#include <iostream>
#include <cassert>
#include "ScoutAlien.h"
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
    InitWindow(800, 600, "Scout Alien Test Results");
    SetTargetFPS(60);
}

// Helper function to cleanup the test environment
void cleanupTestEnvironment() {
    CloseWindow();
}

// Test functions
bool testScoutAlienInitialization() {
    Vector2 pos = {100.0f, 100.0f};
    ScoutAlien alien(pos);

    bool result = (alien.getBoolActive() == true);
    std::cout << "testScoutAlienInitialization " << (result ? "passed!" : "failed!") << std::endl;
    return result;
}

bool testScoutAlienSettersAndGetters() {
    Vector2 pos = {100.0f, 100.0f};
    ScoutAlien alien(pos);

    Vector2 newPos = {150.0f, 150.0f};
    alien.setEnemyPos(newPos);
    bool result = (alien.getScoutSize().x == 15.0f && alien.getScoutSize().y == 15.0f);

    std::cout << "testScoutAlienSettersAndGetters " << (result ? "passed!" : "failed!") << std::endl;
    return result;
}

bool testScoutAlienCollision() {
    Vector2 pos = {100.0f, 100.0f};
    ScoutAlien alien(pos);
    Vector2 entityPos = {95.0f, 95.0f};
    Vector2 entityBox = {10.0f, 10.0f};

    bool result = alien.checkCollisionBox(entityPos, entityBox);
    std::cout << "testScoutAlienCollision " << (result ? "passed!" : "failed!") << std::endl;
    return result;
}

bool testScoutAlienMovement() {
    Vector2 pos = {100.0f, 100.0f};
    ScoutAlien alien(pos);
    alien.setEscapeMode(true);

    float deltaTime = 0.1f; // Simulating 0.1 seconds
    alien.movement(deltaTime, {0.0f, 0.0f}); // Move away from a player at origin

    Vector2 newPos = alien.getCollisionBox(); // Assuming getCollisionBox returns the position
    bool result = (newPos.x != 100.0f || newPos.y != 100.0f);
    std::cout << "testScoutAlienMovement " << (result ? "passed!" : "failed!") << std::endl;
    return result;
}

int main() {
    initTestEnvironment();

    // Run the tests and store the results
    TestResult results[] = {
        {"Test ScoutAlien Initialization", testScoutAlienInitialization()},
        {"Test ScoutAlien Setters and Getters", testScoutAlienSettersAndGetters()},
        {"Test ScoutAlien Collision", testScoutAlienCollision()},
        {"Test ScoutAlien Movement", testScoutAlienMovement()}
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
