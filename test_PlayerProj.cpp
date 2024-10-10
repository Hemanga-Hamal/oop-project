// test_PlayerProj.cpp
#include <iostream>
#include <cassert>
#include "PlayerProj.h"
#include "raylib.h"

void testPlayerProjInitialization() {
    Vector2 pos = {0.0f, 0.0f};
    Vector2 speed = {1.0f, 1.0f};
    PlayerProj proj(pos, speed);

    assert(proj.isActive() == true);
    std::cout << "testPlayerProjInitialization passed!" << std::endl;
}

void testPlayerProjSetters() {
    Vector2 pos = {0.0f, 0.0f};
    Vector2 speed = {1.0f, 1.0f};
    PlayerProj proj(pos, speed);

    Vector2 newPos = {10.0f, 10.0f};
    Vector2 newSpeed = {2.0f, 2.0f};
    int newDamage = 20;

    proj.setProjPos(newPos);
    proj.setProjSpeed(newSpeed);
    proj.setProjDamage(newDamage);

    // Assuming getters exist for these properties
    assert(proj.getProjPos().x == newPos.x);
    assert(proj.getProjPos().y == newPos.y);
    assert(proj.getProjSpeed().x == newSpeed.x);
    assert(proj.getProjSpeed().y == newSpeed.y);
    assert(proj.getProjDamage() == newDamage);

    std::cout << "testPlayerProjSetters passed!" << std::endl;
}

void testPlayerProjEdgeCollision() {
    Vector2 pos = {0.0f, 0.0f};
    Vector2 speed = {1.0f, 1.0f};
    PlayerProj proj(pos, speed);

    proj.setProjPos({-1.0f, 0.0f});
    assert(proj.checkEdgeCollision() == true);

    proj.setProjPos({GetScreenWidth() + 1.0f, 0.0f});
    assert(proj.checkEdgeCollision() == true);

    proj.setProjPos({0.0f, -1.0f});
    assert(proj.checkEdgeCollision() == true);

    proj.setProjPos({0.0f, GetScreenHeight() + 1.0f});
    assert(proj.checkEdgeCollision() == true);

    std::cout << "testPlayerProjEdgeCollision passed!" << std::endl;
}

void testPlayerProjEnemyCollision() {
    Vector2 pos = {0.0f, 0.0f};
    Vector2 speed = {1.0f, 1.0f};
    PlayerProj proj(pos, speed);

    Vector2 enemyPos = {5.0f, 5.0f};
    Vector2 enemyBounding = {10.0f, 10.0f};

    proj.setProjPos({5.0f, 5.0f});
    assert(proj.EnemyCollisionCheck(enemyPos, enemyBounding) == true);

    proj.setProjPos({15.0f, 15.0f});
    assert(proj.EnemyCollisionCheck(enemyPos, enemyBounding) == false);

    std::cout << "testPlayerProjEnemyCollision passed!" << std::endl;
}

void testPlayerProjUpdate() {
    Vector2 pos = {0.0f, 0.0f};
    Vector2 speed = {1.0f, 1.0f};
    PlayerProj proj(pos, speed);

    proj.update(1.0f); // Update for 1 second

    assert(proj.getProjPos().x == 1.0f);
    assert(proj.getProjPos().y == 1.0f);

    std::cout << "testPlayerProjUpdate passed!" << std::endl;
}

int main() {
    InitWindow(800, 600, "Test Window"); // Required for GetScreenWidth() and GetScreenHeight()

    testPlayerProjInitialization();
    testPlayerProjSetters();
    testPlayerProjEdgeCollision();
    testPlayerProjEnemyCollision();
    testPlayerProjUpdate();

    std::cout << "All tests passed!" << std::endl;

    CloseWindow(); // Close the window
    return 0;
}