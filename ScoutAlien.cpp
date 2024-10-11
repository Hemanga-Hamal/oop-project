#include "ScoutAlien.h"
#include "raymath.h"

// Constructor and Destructor
ScoutAlien::ScoutAlien(Vector2 pos) : Alien(pos, {0,0}, 1) {
    this->enemy_speed = speed;
    this->enemy_health = health;
    this->alien_size = size;
    escapeMode = false;
    randomMoveTimer = GetRandomValue(2, 5);  
}
ScoutAlien::~ScoutAlien() {}

// Setters
void ScoutAlien::setEnemyPos(Vector2 newPos)            { enemy_pos = newPos; }
void ScoutAlien::setEnemySpeed(Vector2 newSpeed)        { enemy_speed = newSpeed; }
void ScoutAlien::setAlienSize(Vector2 newSize)          { alien_size = newSize; }
void ScoutAlien::setCollisionBox(Vector2 newBox)        { alien_collision_box = newBox; }
void ScoutAlien::setEnemyHealth(int newHealth)          { enemy_health = newHealth; }
void ScoutAlien::setAlienRotation(int newRotation)      { alien_rotation = newRotation; }
void ScoutAlien::setBoolActive(bool newActive)          { active = newActive; }
void ScoutAlien::setEscapeMode(bool newMode)            { escapeMode = newMode; }

// Getters
Vector2 ScoutAlien::getScoutSize()      { return alien_size; }
Vector2 ScoutAlien::getCollisionBox()   { return alien_collision_box; }
int ScoutAlien::getScoutRotation()      { return alien_rotation; }
bool ScoutAlien::getBoolActive()        { return active; }
bool ScoutAlien::getEscapeMode()        { return escapeMode; }

// Collision detection
bool ScoutAlien::checkCollisionBox(Vector2 entityPos, Vector2 entityBox) {
    if (!active) return false;
    Vector2 relativePos = Vector2Subtract(enemy_pos, entityPos);
    Vector2 rotatedPos = Vector2Rotate(relativePos, -alien_rotation * DEG2RAD); 
    bool insideBox = (rotatedPos.x >= -alien_collision_box.x / 2 && rotatedPos.x <=alien_collision_box.x / 2 
                     && rotatedPos.y >= -alien_collision_box.y / 2 && rotatedPos.y <= alien_collision_box.y / 2);
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
    DrawRectangleV(enemy_pos, alien_size, alien_color);  
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
