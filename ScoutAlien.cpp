#include "ScoutAlien.h"
#include "raymath.h"

// Constructor and Destructor
ScoutAlien::ScoutAlien(Vector2 pos, Vector2 speed, int health) : Enemy(pos, speed, health) {
    escapeMode = false;
    randomMoveTimer = GetRandomValue(2, 5);
}
ScoutAlien::~ScoutAlien (){}

// Setters
void ScoutAlien::setScoutSize(Vector2 newSize){size = newSize;}
void ScoutAlien::setcollisionBox(Vector2 newBox){collisionBox = newBox;}
void ScoutAlien::setScoutRotation(int newRotation){rotation = newRotation;}

// Getters
Vector2 ScoutAlien::getScoutSize(){return size;}
Vector2 ScoutAlien::getcollisionBox(){return collisionBox;}
int ScoutAlien::getScoutRotation(){return rotation;}

// Collision
bool ScoutAlien::CheckCollisionBoxes(Vector2 entityPos, Vector2 entityBox) {
    if (!active) return false;
    Vector2 relativePos = Vector2Subtract(enemy_pos, entityPos);
    Vector2 rotatedPos = Vector2Rotate(relativePos, -rotation);
    bool insideBox = (rotatedPos.x >= -collisionBox.x / 2 && rotatedPos.x <= collisionBox.x / 2 
                     && rotatedPos.y >= -collisionBox.y / 2 && rotatedPos.y <= collisionBox.y / 2);
    return insideBox;
}

// Movement - ScoutAlien moves randomly until it sees the player, then flies off screen
void ScoutAlien::movement(float deltaTime, Vector2 playerPos) {
    if (escapeMode) {

        enemy_pos.x += enemy_speed.x * deltaTime * escapeSpeed;
        enemy_pos.y += enemy_speed.y * deltaTime * escapeSpeed;

        if (enemy_pos.x < 0 || enemy_pos.x > GetScreenWidth() || enemy_pos.y < 0 || enemy_pos.y > GetScreenHeight()) {
            active = false;
        }
    } else {
        randomMoveTimer -= deltaTime;
        // If it's time to change direction, pick a new random direction
        if (randomMoveTimer <= 0.0f) {
            float randomAngle = GetRandomValue(0, 360) * DEG2RAD;
            Vector2 randomDir = { cosf(randomAngle), sinf(randomAngle) };
            enemy_speed = Vector2Scale(Vector2Normalize(randomDir), 100.0f); 
            randomMoveTimer = GetRandomValue(2, 5);
        }
        
        enemy_pos.x += enemy_speed.x * deltaTime;
        enemy_pos.y += enemy_speed.y * deltaTime;

        // Keep the alien within the screen bounds
        if (enemy_pos.x < 0) enemy_pos.x = GetScreenWidth();
        if (enemy_pos.x > GetScreenWidth()) enemy_pos.x = 0;
        if (enemy_pos.y < 0) enemy_pos.y = GetScreenHeight();
        if (enemy_pos.y > GetScreenHeight()) enemy_pos.y = 0;

        // Player detection: Check if the alien is close enough to detect the player
        if (Vector2Distance(enemy_pos, playerPos) < detectionRange) {
            escapeMode = true;
            Vector2 directionAwayFromPlayer = Vector2Normalize(Vector2Subtract(enemy_pos, playerPos));
            enemy_speed = directionAwayFromPlayer;
        }
    }
}

// Updating and Rendering
void ScoutAlien::draw(){DrawRectangleV(enemy_pos, size, color);}

void ScoutAlien::update(float deltaTime, Vector2 playerPos){
    movement(deltaTime, playerPos);
    draw();
}
