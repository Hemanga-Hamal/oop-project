#include "Asteroids.h"
#include "raymath.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Constructor
Asteroids::Asteroids(Vector2 pos, Vector2 speed) : Enemy(pos, speed, 0), active(true) {
    asterScale = (GetRandomValue(85, 215) / 100.0f);  // Scale range updated
    enemy_health = static_cast<int>(20 * asterScale);
    asterDmg = static_cast<int>(10 * asterScale);
    Aster_Bounding = { static_cast<float>(30 * asterScale), static_cast<float>(30 * asterScale) };
    // Starts random seed on each run by taking time since epoch
    std::srand(static_cast<unsigned int>(std::time(0)));
    spawnAtEdge();
}

void Asteroids::spawnAtEdge(){
    // Generates a random value between 0 and 3 for the 4 edges of the screen
    int edgeCase = std::rand() % 4;
    switch (edgeCase){
        case 0:
            // Random x coord within width range
            enemy_pos.x = static_cast<float>(std::rand() % GetScreenWidth());
            // Y coord at the top
            enemy_pos.y = 0;
            break;
        case 1:
            // Random x coord within width range
            enemy_pos.x = static_cast<float>(std::rand() % GetScreenWidth());
            // Y coord at the bottom
            enemy_pos.y = GetScreenHeight();
            break;
        case 2:
            // X coord on the left 
            enemy_pos.x = 0;
            // Random y coord within height range
            enemy_pos.y = static_cast<float>(std::rand() % GetScreenHeight());
            break;
        case 3:
            // X coord on the right
            enemy_pos.x = GetScreenWidth();
            // Random y coord within height range
            enemy_pos.y = static_cast<float>(std::rand() % GetScreenHeight());
            break;
    }
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

// Update
void Asteroids::update(float deltaTime) {
    if (!active) return;

    movement(deltaTime);
    draw();
}

// Set speed towards a target
void Asteroids::setSpeedTowards(Vector2 target, float baseSpeed) {
    if (!active) return;

    Vector2 direction = Vector2Subtract(target, enemy_pos);
    direction = Vector2Normalize(direction);

    // Adjust speed inversely with the asteroid's scale
    // To make the scaling more visible, use a scaling factor
    float speedScalingFactor = 2.0f; // Adjust this factor to control speed scaling
    float adjustedSpeed = (baseSpeed / asterScale) * speedScalingFactor;
    setEnemySpeed(Vector2Scale(direction, adjustedSpeed));
}

// Reset asteroid position, speed, and size
void Asteroids::reset(Vector2 newPos, Vector2 playerPos, float baseSpeed, float scale) {
    setActive(true); // Set to active
    setEnemyPos(newPos);

    if (scale <= 0.0f) {
        asterScale = (GetRandomValue(85, 215) / 100.0f); 
    } else {
        asterScale = scale;
    }
    asterDmg = static_cast<int>(10 * asterScale);
    Aster_Bounding = { static_cast<float>(30 * asterScale), static_cast<float>(30 * asterScale) };

    setSpeedTowards(playerPos, baseSpeed); 
}
