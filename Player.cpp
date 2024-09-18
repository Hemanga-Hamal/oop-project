#include "Player.h"
#include "raymath.h"
#include <cmath>

Player::Player(Vector2 pos, int health) : pl_pos(pos), pl_health(health){}

Player::~Player() {}

// Setters
void Player::setPLHealth(int health)            { pl_health = health;   }
void Player::setPLSpeed(const Vector2& speed)   { pl_speed = speed;     }
void Player::setRotation(float rotation)        { pl_rot = rotation;    }

// Getters
Vector2 Player::getPLPos()      const { return pl_pos;      }
Vector2 Player::getPLSpeed()    const { return pl_speed;    }
int Player::getPLHealth()       const { return pl_health;   }
float Player::getRotation()     const { return pl_rot;      }

// Movement
void Player::movement(float deltaTime) {
    if (IsKeyDown(KEY_W)) pl_pos.y -= pl_speed.y * deltaTime;
    if (IsKeyDown(KEY_S)) pl_pos.y += pl_speed.y * deltaTime;
    if (IsKeyDown(KEY_A)) pl_pos.x -= pl_speed.x * deltaTime;
    if (IsKeyDown(KEY_D)) pl_pos.x += pl_speed.x * deltaTime;

    // Wrap around screen edges
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    if (pl_pos.x < 0) pl_pos.x = screenWidth;
    if (pl_pos.x > screenWidth) pl_pos.x = 0;
    if (pl_pos.y < 0) pl_pos.y = screenHeight;
    if (pl_pos.y > screenHeight) pl_pos.y = 0;
}

//Collision logic
bool Player::checkColEnemy(Vector2 enemyPos, Vector2 enemyBounding) {
    Vector2 relativePos = Vector2Subtract(enemyPos, pl_pos);
    Vector2 rotatedPos = Vector2Rotate(relativePos, -pl_rot);

    float normX = rotatedPos.x / halfWidth;
    float normY = rotatedPos.y / halfHeight;
    bool insideEllipse = (normX * normX + normY * normY <= 1.0f);
    
    if (insideEllipse)  {return true;}

    float angle = atan2f(rotatedPos.y, rotatedPos.x);
    float ellipseX = halfWidth * cosf(angle);
    float ellipseY = halfHeight * sinf(angle);
    float dist_x = rotatedPos.x - ellipseX;
    float dist_y = rotatedPos.y - ellipseY;
    float distance = sqrtf(dist_x * dist_x + dist_y * dist_y);

    return distance < enemyBounding.x|| distance < enemyBounding.y;
}



// Rendering
void Player::updateRotation(Vector2 mousePos) {
    Vector2 direction = { mousePos.x - pl_pos.x, mousePos.y - pl_pos.y };
    pl_rot = atan2f(direction.y, direction.x) + (float)PI / 2.0f;
}

void Player::takeDamage(int damage) {
    pl_health -= damage;
    pl_flashRedTimeRemaining = flashRedDuration;
}

void Player::draw() {
    // Draw the player triangle
    float size = 23.0f;
    v1 = { pl_pos.x, pl_pos.y - size};
    v2 = { pl_pos.x - size / 2, pl_pos.y + size / 2 +2};
    v3 = { pl_pos.x + size / 2, pl_pos.y + size / 2 +2};
    Vector2 center = pl_pos;

    v1 = Vector2Rotate(Vector2Subtract(v1, center), pl_rot);
    v1 = Vector2Add(v1, center);
    v2 = Vector2Rotate(Vector2Subtract(v2, center), pl_rot);
    v2 = Vector2Add(v2, center);
    v3 = Vector2Rotate(Vector2Subtract(v3, center), pl_rot);
    v3 = Vector2Add(v3, center);

    pl_colour = (pl_flashRedTimeRemaining > 0.0f) ? RED : BLUE;
    DrawTriangle(v1, v2, v3, pl_colour);

    //bouding oval testing
    if (true){
    float halfWidth = 10.0f;
    float halfHeight = 20.0f;
    int numSegments = 64;
    for (int i = 0; i < numSegments; i++) {
        float angle1 = (float)i / numSegments * 2.0f * PI;
        float angle2 = (float)(i + 1) / numSegments * 2.0f * PI;
        Vector2 p1 = { pl_pos.x + halfWidth * cosf(angle1), pl_pos.y + halfHeight * sinf(angle1) };
        Vector2 p2 = { pl_pos.x + halfWidth * cosf(angle2), pl_pos.y + halfHeight * sinf(angle2) };
        p1 = Vector2Rotate(Vector2Subtract(p1, center), pl_rot);
        p1 = Vector2Add(p1, center);
        p2 = Vector2Rotate(Vector2Subtract(p2, center), pl_rot);
        p2 = Vector2Add(p2, center);
        DrawLineV(p1, p2, DARKGRAY);
    }
    }
}

// Update
void Player::update(float deltaTime) {
    //movement
    movement(deltaTime);

    //model Rotation
    Vector2 mousePos = GetMousePosition();
    updateRotation(mousePos);

    //Take damage colour swap
     if (pl_flashRedTimeRemaining > 0.0f) {
        pl_flashRedTimeRemaining -= deltaTime;
    }
}
