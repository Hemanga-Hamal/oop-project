#include "Asteroids.h"
#include "raymath.h"
#include "Player.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Constructor
Asteroids::Asteroids(Vector2 pos, Vector2 speed) : Enemy(pos, speed, 0), active(true) {
    asterScale = (GetRandomValue(85, 215) / 100.0f); 
    enemy_health = static_cast<int>(20 * asterScale);
    asterDmg = static_cast<int>(10 * asterScale);
    Aster_Bounding = { static_cast<float>(30 * asterScale), static_cast<float>(30 * asterScale) };
    spawnAtEdge();
}

// Check size of the asteroid
int Asteroids::checkSize() {
    if (Aster_Bounding.x <= 38) {
        return 1; // Small
    } else if (Aster_Bounding.x <= 51.5) {
        return 2; // Medium
    } else {
        return 3; // Big
    }
}

// Break apart the asteroid
void Asteroids::breakApart(std::vector<std::unique_ptr<Asteroids>>& asteroidsList) {
    int size = checkSize();
    int numNewAsteroids = 0;

    switch (size) {
        case 3: // Big asteroid
            numNewAsteroids = 2;
            break;
        case 2: // Medium asteroid
            numNewAsteroids = 2;
            break; 
        case 1: // Small asteroid
            setActive(false);
            return; // Small asteroids are destroyed
    }

    for (int i = 0; i < numNewAsteroids; ++i) {
        // Create a new asteroid and set its properties
        auto newAsteroid = std::make_unique<Asteroids>(enemy_pos, Vector2{0.0f, 0.0f});
        newAsteroid->asterScale = 0.85f; // Adjust size
        newAsteroid->Aster_Bounding = { static_cast<float>(30 * newAsteroid->asterScale), 
                                         static_cast<float>(30 * newAsteroid->asterScale) };

        float randomAngle = GetRandomValue(0, 360) * DEG2RAD;
        Vector2 randomDir = { cosf(randomAngle), sinf(randomAngle)};
        randomDir = Vector2Normalize(randomDir);

        float speedFactor = 180.0f; // Adjust speed for new asteroids
        newAsteroid->setEnemySpeed(Vector2Scale(randomDir, speedFactor));

        asteroidsList.push_back(std::move(newAsteroid));
    }

    setActive(false); // Mark this asteroid as inactive
}

// Spawn the asteroid at a random edge of the screen
void Asteroids::spawnAtEdge() {
    int edgeCase = std::rand() % 4;
    switch (edgeCase) {
        case 0:
            enemy_pos.x = static_cast<float>(std::rand() % GetScreenWidth());
            enemy_pos.y = 0; // Top
            break;
        case 1:
            enemy_pos.x = static_cast<float>(std::rand() % GetScreenWidth());
            enemy_pos.y = GetScreenHeight(); // Bottom
            break;
        case 2:
            enemy_pos.x = 0; // Left
            enemy_pos.y = static_cast<float>(std::rand() % GetScreenHeight());
            break;
        case 3:
            enemy_pos.x = GetScreenWidth(); // Right
            enemy_pos.y = static_cast<float>(std::rand() % GetScreenHeight());
            break;
    }
    setActive(true);
}

// Setters
void Asteroids::setEnemyPos(Vector2 pos) { enemy_pos = pos; }
void Asteroids::setEnemySpeed(Vector2 speed) { enemy_speed = speed; }
void Asteroids::setEnemyHealth(int health) { enemy_health = health; }
void Asteroids::setActive(bool state) { active = state; }

// Getters
int Asteroids::getAsteroidsDamage() const { return asterDmg; }
float Asteroids::getAsteroidsScale() const { return asterScale; }
Vector2 Asteroids::getAsteroidsBounding() const { return Aster_Bounding; }
bool Asteroids::isActive() const { return active; }

// Take damage
void Asteroids::takeDamage(int damage) {
    enemy_health -= damage;
    if (enemy_health <= 0) {
        setActive(false); // Deactivate if health is zero
    }
}

// Movement
void Asteroids::movement(float deltaTime) {
    if (!active) return;

    enemy_pos.x += enemy_speed.x * deltaTime;
    enemy_pos.y += enemy_speed.y * deltaTime;

    // Deactivate if out of bounds
    if (enemy_pos.x < 0 || enemy_pos.x > GetScreenWidth() ||
        enemy_pos.y < 0 || enemy_pos.y > GetScreenHeight()) {
        setActive(false);
    }
}

// Collision logic
bool Asteroids::checkColPlayer(Vector2 playerPos, Vector2 playerBounding, float pl_rot) {
    if (!active) return false;

    Vector2 relativePos = Vector2Subtract(playerPos, enemy_pos);
    Vector2 rotatedPos = Vector2Rotate(relativePos, -pl_rot);

    float normX = rotatedPos.x / (playerBounding.x);
    float normY = rotatedPos.y / (playerBounding.y);
    bool insideEllipse = (normX * normX + normY * normY <= 1.0f);

    if (insideEllipse) { return true; }

    float angle = atan2f(rotatedPos.y, rotatedPos.x);
    float ellipseX = (playerBounding.x) * cosf(angle);
    float ellipseY = (playerBounding.y) * sinf(angle);
    float dist_x = rotatedPos.x - ellipseX;
    float dist_y = rotatedPos.y - ellipseY;
    float distance = sqrtf(dist_x * dist_x + dist_y * dist_y);

    return distance < (Aster_Bounding.x / 2);
}

// Draw
void Asteroids::draw() {
    if (active) {
        DrawCircleV(enemy_pos, Aster_Bounding.x / 2, GRAY);
    }
}

// Set speed towards a target
void Asteroids::setSpeedTowards(Vector2 target, float baseSpeed) {
    if (!active) return;

    Vector2 direction = Vector2Subtract(target, enemy_pos);
    direction = Vector2Normalize(direction);

    float speedScalingFactor = 2.0f;
    float adjustedSpeed = (baseSpeed / asterScale) * speedScalingFactor;
    setEnemySpeed(Vector2Scale(direction, adjustedSpeed));
}

// Handles asteroid spawning after destruction
void Asteroids::spawnNewAsteroid(Vector2 playerPos, float baseSpeed) {
    asterScale = (GetRandomValue(85, 215) / 100.0f); 
    enemy_health = static_cast<int>(20 * asterScale);
    asterDmg = static_cast<int>(10 * asterScale);
    Aster_Bounding = { static_cast<float>(30 * asterScale), static_cast<float>(30 * asterScale) };
    spawnAtEdge();  
    setSpeedTowards(playerPos, baseSpeed); 
}

// Handles collision with the player and asteroid destruction
bool Asteroids::handlePlayerCollision(Vector2 playerPos, Vector2 playerBounding, float pl_rot, Player& player) {
    if (checkColPlayer(playerPos, playerBounding, pl_rot)) {
        player.takeDamage(getAsteroidsDamage());
        setActive(false);
        return true;
    }
    return false;
}

// Update overide
void Asteroids::update(float deltaTime) {
    if (!active) return;

    movement(deltaTime);
    draw();
}

// Update asteroid state, check collisions, respawn if necessary
void Asteroids::update(float deltaTime, Vector2 playerPos, float baseSpeed, Player& player, std::vector<std::unique_ptr<Asteroids>>& asteroidsList) {
    if (!active) return;

    movement(deltaTime);

    if (handlePlayerCollision(player.getPLPos(), player.getBoundingBox(), 0.0f, player)) {
        breakApart(asteroidsList);
    } 
    else if (!isActive()) {
        spawnNewAsteroid(player.getPLPos(), baseSpeed);
    }

    draw();
}