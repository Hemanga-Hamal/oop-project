// test_Asteroids.cpp
#include <iostream>
#include <cassert>
#include "Asteroids.h"
#include "raylib.h"

// Helper function to initialize the test environment
void initTestEnvironment() {
    InitWindow(800, 600, "Test Window");
    SetTargetFPS(60);
}

// Helper function to cleanup the test environment
void cleanupTestEnvironment() {
    CloseWindow();
}

// Test drawing when the asteroid is active
void testAsteroidsDrawActive() {
    initTestEnvironment();

    Vector2 pos = {400.0f, 300.0f};
    Vector2 speed = {0.0f, 0.0f};
    Asteroids asteroid(pos, speed);

    asteroid.setActive(true);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    asteroid.draw();
    EndDrawing();

    // Placeholder assertion
    assert(asteroid.isActive() == true);

    std::cout << "testAsteroidsDrawActive passed!" << std::endl;

    cleanupTestEnvironment();
}

// Test drawing when the asteroid is inactive
void testAsteroidsDrawInactive() {
    initTestEnvironment();

    Vector2 pos = {400.0f, 300.0f};
    Vector2 speed = {0.0f, 0.0f};
    Asteroids asteroid(pos, speed);

    asteroid.setActive(false);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    asteroid.draw();
    EndDrawing();

    // Placeholder assertion
    assert(asteroid.isActive() == false);

    std::cout << "testAsteroidsDrawInactive passed!" << std::endl;

    cleanupTestEnvironment();
}

// Test asteroid movement
void testAsteroidsMovement() {
    Vector2 pos = {400.0f, 300.0f};
    Vector2 speed = {100.0f, 0.0f}; // Move right
    Asteroids asteroid(pos, speed);

    float deltaTime = 1.0f; // Simulate 1 second
    asteroid.movement(deltaTime);

    assert(asteroid.getEnemyPos().x == 500.0f); // Should have moved 100 units to the right
    assert(asteroid.getEnemyPos().y == 300.0f); // Y position should remain the same

    std::cout << "testAsteroidsMovement passed!" << std::endl;
}

// Test asteroid collision with player
void testAsteroidsCollisionWithPlayer() {
    Vector2 asteroidPos = {400.0f, 300.0f};
    Vector2 asteroidSpeed = {0.0f, 0.0f};
    Asteroids asteroid(asteroidPos, asteroidSpeed);

    Vector2 playerPos = {400.0f, 300.0f};
    Vector2 playerBounding = {50.0f, 50.0f};
    float playerRotation = 0.0f;

    bool collision = asteroid.checkColPlayer(playerPos, playerBounding, playerRotation);

    assert(collision == true); // Should collide

    std::cout << "testAsteroidsCollisionWithPlayer passed!" << std::endl;
}

// Test asteroid breaking apart
void testAsteroidsBreakApart() {
    Vector2 pos = {400.0f, 300.0f};
    Vector2 speed = {0.0f, 0.0f};
    Asteroids asteroid(pos, speed);

    std::vector<std::unique_ptr<Asteroids>> asteroidsList;
    asteroid.breakApart(asteroidsList);

    assert(asteroidsList.size() > 0); // Should have created new asteroids

    std::cout << "testAsteroidsBreakApart passed!" << std::endl;
}

int main() {
    testAsteroidsDrawActive();
    testAsteroidsDrawInactive();
    testAsteroidsMovement();
    testAsteroidsCollisionWithPlayer();
    testAsteroidsBreakApart();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}