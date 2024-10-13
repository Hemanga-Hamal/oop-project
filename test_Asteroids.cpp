#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <memory>
#include "Asteroids.h"
#include "raylib.h"

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

// Helper function to initialize the test environment
void initTestEnvironment() {
    InitWindow(800, 600, "Asteroid Test Results");
    SetTargetFPS(60);
}

// Helper function to cleanup the test environment
void cleanupTestEnvironment() {
    CloseWindow();
}

// Test drawing when the asteroid is active
bool testAsteroidsDrawActive() {
    Vector2 pos = {400.0f, 300.0f};
    Vector2 speed = {0.0f, 0.0f};
    Asteroids asteroid(pos, speed);
    asteroid.setActive(true);

    // Check if the asteroid is active
    return asteroid.isActive() == true;
}

// Test drawing when the asteroid is inactive
bool testAsteroidsDrawInactive() {
    Vector2 pos = {400.0f, 300.0f};
    Vector2 speed = {0.0f, 0.0f};
    Asteroids asteroid(pos, speed);
    asteroid.setActive(false);

    // Check if the asteroid is inactive
    return asteroid.isActive() == false;
}

// Test asteroid movement
bool testAsteroidsMovement() {
    Vector2 initialPos = {400.0f, 300.0f};
    Vector2 initialSpeed = {0.0f, 0.0f};
    Asteroids asteroid(initialPos, initialSpeed);
    asteroid.setActive(true); // Make sure the asteroid is active

    // Move the asteroid to the right
    asteroid.setEnemySpeed({10.0f, 0.0f});
    asteroid.movement(1.0f); // Move for 1 second

    // Now, asteroid's position should be (410.0, 300.0)
    Vector2 intermediatePos = asteroid.getEnemyPos();
    std::cout << "Intermediate Position After Right Move: (" << intermediatePos.x << ", " << intermediatePos.y << ")\n";

    Vector2 finalPos = asteroid.getEnemyPos();
    std::cout << "Final Position After Left Move: (" << finalPos.x << ", " << finalPos.y << ")\n";

    // Check if the final position is back at the initial position
    return finalPos.x == 534.0f && finalPos.y == 600.0f;
}

bool testCollisionDetected() {
    Vector2 asteroidPos = {400.0f, 300.0f};
    Vector2 asteroidSpeed = {0.0f, 0.0f};
    Asteroids asteroid(asteroidPos, asteroidSpeed);
    asteroid.setActive(true);

    // Player's position and bounding box overlapping with the asteroid
    Vector2 playerPos = {asteroid.getEnemyPos()}; // Same position as the asteroid
    Vector2 playerBounding = {50.0f, 50.0f}; // Example bounding box
    float playerRotation = 0.0f; // No rotation

    bool collisionDetected = asteroid.checkColPlayer(playerPos, playerBounding, playerRotation);
    std::cout << "Basic Collision Detected: " << (collisionDetected ? "Yes" : "No") << "\n";

    return collisionDetected; // Expect true
}


// Test asteroid breaking apart
bool testAsteroidsBreakApart() {
    Vector2 pos = {400.0f, 300.0f};
    Vector2 speed = {0.0f, 0.0f};
    Asteroids asteroid(pos, speed);
    asteroid.setActive(true);

    asteroid.setEnemyHealth(50);
    std::vector<std::unique_ptr<Asteroids>> asteroidsList;
    asteroid.breakApart(asteroidsList);

    // Expect at least one smaller asteroid to be created
    return asteroidsList.size() > 0; // Should have created new asteroids
}

int main() {
    initTestEnvironment();

    // Run the tests and store the results
    TestResult results[] = {
        {"Test Asteroids Draw Active", testAsteroidsDrawActive()},
        {"Test Asteroids Draw Inactive", testAsteroidsDrawInactive()},
        {"Test Asteroids Movement", testAsteroidsMovement()},
        {"Test Asteroids Collision With Player", testCollisionDetected()},
        {"Test Asteroids Break Apart", testAsteroidsBreakApart()}
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
