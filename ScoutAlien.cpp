#include "ScoutAlien.h"
#include "raymath.h"

// Constructor and Destructor
ScoutAlien::ScoutAlien(Vector2 pos) : Alien(pos, {0,0}, 1) {
    this->enemy_speed = speed;
    this->enemy_health = health;
    escapeMode = false;
    randomMoveTimer = GetRandomValue(2, 5);  
}
ScoutAlien::~ScoutAlien() {}

// Setters
void ScoutAlien::setEnemyPos(Vector2 newPos)            { enemy_pos = newPos; }
void ScoutAlien::setEnemySpeed(Vector2 newSpeed)        { enemy_speed = newSpeed; }
void ScoutAlien::setScoutSize(Vector2 newSize)          { size = newSize; }
void ScoutAlien::setcollisionBox(Vector2 newBox)        { collisionBox = newBox; }
void ScoutAlien::setEnemyHealth(int newHealth)          { enemy_health = newHealth; }
void ScoutAlien::setScoutRotation(int newRotation)      { rotation = newRotation; }
void ScoutAlien::setboolactive(bool newActive)          { active = newActive; }
void ScoutAlien::setEscapeMode(bool newMode)            { escapeMode = newMode; }

// Getters
Vector2 ScoutAlien::getScoutSize()      { return size; }
Vector2 ScoutAlien::getcollisionBox()   { return collisionBox; }
int ScoutAlien::getScoutRotation()      { return rotation; }
bool ScoutAlien::getboolactive()        { return active; }
bool ScoutAlien::getEscapeMode()        { return escapeMode; }

// Collision detection
bool ScoutAlien::CheckCollisionBoxes(Vector2 entityPos, Vector2 entityBox) {
    if (!active) return false;
    Vector2 relativePos = Vector2Subtract(enemy_pos, entityPos);
    Vector2 rotatedPos = Vector2Rotate(relativePos, -rotation * DEG2RAD); 
    bool insideBox = (rotatedPos.x >= -collisionBox.x / 2 && rotatedPos.x <= collisionBox.x / 2 
                     && rotatedPos.y >= -collisionBox.y / 2 && rotatedPos.y <= collisionBox.y / 2);
    return insideBox;
}

// Movement logic
void ScoutAlien::movement(float deltaTime) {
    Vector2 defaultPlayerPos = {0, 0};
    movement(deltaTime, defaultPlayerPos);
}

void ScoutAlien::movement(float deltaTime, Vector2 playerPos) {
    if (escapeMode) {
        // Escape mode: move quickly away from the player
        enemy_pos.x += enemy_speed.x * escapeSpeed * deltaTime;
        enemy_pos.y += enemy_speed.y * escapeSpeed * deltaTime;

        // Check if the alien has moved off-screen, deactivate it
        if (enemy_pos.x < 0 || enemy_pos.x > GetScreenWidth() || enemy_pos.y < 0 || enemy_pos.y > GetScreenHeight()) {
            active = false; 
        }
    } else {
        // Exploration mode: random movement
        randomMoveTimer -= deltaTime;
        
        if (randomMoveTimer <= 0.0f) {
            // Pick a new random direction
            float randomAngle = GetRandomValue(0, 360) * DEG2RAD;
            Vector2 randomDir = { cosf(randomAngle), sinf(randomAngle) };
            enemy_speed = Vector2Scale(Vector2Normalize(randomDir), 100.0f);
            randomMoveTimer = GetRandomValue(2, 5); 
        }

        // Move the alien in the current direction
        enemy_pos.x += enemy_speed.x * deltaTime;
        enemy_pos.y += enemy_speed.y * deltaTime;

        // Wrap the alien around the screen
        if (enemy_pos.x < 0) enemy_pos.x = GetScreenWidth();
        if (enemy_pos.x > GetScreenWidth()) enemy_pos.x = 0;
        if (enemy_pos.y < 0) enemy_pos.y = GetScreenHeight();
        if (enemy_pos.y > GetScreenHeight()) enemy_pos.y = 0;

        // Detect player and switch to escape mode if within detection range
        if (Vector2Distance(enemy_pos, playerPos) < detectionRange) {
            escapeMode = true;
            Vector2 directionAwayFromPlayer = Vector2Normalize(Vector2Subtract(enemy_pos, playerPos));
            enemy_speed = directionAwayFromPlayer; 
        }
    }
}

// Draw
void ScoutAlien::draw() {
    DrawRectangleV(enemy_pos, size, color);  
}

// Update
void ScoutAlien::update(float deltaTime) {
    Vector2 defaultPlayerPos = {0, 0};
    update(deltaTime, defaultPlayerPos);
}

void ScoutAlien::update(float deltaTime, Vector2 playerPos) {
    movement(deltaTime, playerPos);  
    draw(); 
}
