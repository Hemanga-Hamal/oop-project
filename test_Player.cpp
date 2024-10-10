#include <iostream>
#include <cassert>
#include "math.h"
#include "Player.h"

void testPlayerInitialization() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    assert(player.getPLPos().x == initialPos.x);
    assert(player.getPLPos().y == initialPos.y);
    assert(player.getPLHealth() == initialHealth);

    std::cout << "testPlayerInitialization passed!" << std::endl;
}

void testPlayerMovement() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    player.setPLSpeed({10.0f, 0.0f});
    player.movement(1.0f); // Move for 1 second

    assert(player.getPLPos().x == 10.0f);
    assert(player.getPLPos().y == 0.0f);

    std::cout << "testPlayerMovement passed!" << std::endl;
}
#include <iostream>
#include <cassert>
#include "Player.h"

void testPlayerInitialization() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    assert(player.getPLPos().x == initialPos.x);
    assert(player.getPLPos().y == initialPos.y);
    assert(player.getPLHealth() == initialHealth);

    std::cout << "testPlayerInitialization passed!" << std::endl;
}

void testPlayerMovement() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    player.setPLSpeed({10.0f, 0.0f});
    player.movement(1.0f); // Move for 1 second

    assert(player.getPLPos().x == 10.0f);
    assert(player.getPLPos().y == 0.0f);

    std::cout << "testPlayerMovement passed!" << std::endl;
}

void testPlayerShoot() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    player.shoot();
    assert(player.getActiveBulletCount() == 1);

    std::cout << "testPlayerShoot passed!" << std::endl;
}

void testPlayerTakeDamage() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    player.takeDamage(10);
    assert(player.getPLHealth() == 90);

    std::cout << "testPlayerTakeDamage passed!" << std::endl;
}

void testPlayerCollision() {
    Vector2 playerPos = {0.0f, 0.0f};
    int playerHealth = 100;
    Player player(playerPos, playerHealth);

    Vector2 enemyPos = {5.0f, 5.0f};
    Vector2 enemyBounding = {10.0f, 10.0f};

    bool collision = player.checkColEnemy(enemyPos, enemyBounding);
    assert(collision == true);

    std::cout << "testPlayerCollision passed!" << std::endl;
}

void testPlayerRotation() {
    Vector2 initialPos = {0.0f, 0.0f};
    int initialHealth = 100;
    Player player(initialPos, initialHealth);

    Vector2 mousePos = {10.0f, 0.0f};
    player.updateRotation(mousePos);

    assert(player.getRotation() == atan2f(0.0f, 10.0f) + (float)PI / 2.0f);

    std::cout << "testPlayerRotation passed!" << std::endl;
}

int main() {
    testPlayerInitialization();
    testPlayerRotation();
    testPlayerMovement();
    testPlayerShoot();
    testPlayerTakeDamage();
    testPlayerCollision();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}