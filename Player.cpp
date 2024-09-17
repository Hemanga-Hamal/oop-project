#include "Player.h"
#include "raymath.h"
#include <cmath>

Player::Player(float x, float y, Vector2 speed, float rotation, int health)
     : pl_pos({x, y}), pl_speed(speed), pl_rot(rotation), pl_health(health) {}

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
void Player::up(float deltaTime)    { pl_pos.y -= pl_speed.y * deltaTime; }
void Player::down(float deltaTime)  { pl_pos.y += pl_speed.y * deltaTime; }
void Player::left(float deltaTime)  { pl_pos.x -= pl_speed.x * deltaTime; }
void Player::right(float deltaTime) { pl_pos.x += pl_speed.x * deltaTime; }

//

// Rendering
void Player::updateRotation(Vector2 mousePos) {
    Vector2 direction = { mousePos.x - pl_pos.x, mousePos.y - pl_pos.y };
    pl_rot = atan2f(direction.y, direction.x) + (float)PI / 2.0f;
}
void Player::draw() const {
    float size = 20.0f;
    Vector2 v1 = { pl_pos.x, pl_pos.y - size };
    Vector2 v2 = { pl_pos.x - size / 2, pl_pos.y + size / 2 }; 
    Vector2 v3 = { pl_pos.x + size / 2, pl_pos.y + size / 2 };
    Vector2 center = pl_pos;
    v1 = Vector2Rotate(Vector2Subtract(v1, center), pl_rot);
    v1 = Vector2Add(v1, center);
    v2 = Vector2Rotate(Vector2Subtract(v2, center), pl_rot);
    v2 = Vector2Add(v2, center);
    v3 = Vector2Rotate(Vector2Subtract(v3, center), pl_rot);
    v3 = Vector2Add(v3, center);
    DrawTriangle(v1, v2, v3, BLUE);
}

// Update
void Player::update(float deltaTime) {
    if (IsKeyDown(KEY_W)) up(deltaTime);
    if (IsKeyDown(KEY_S)) down(deltaTime);
    if (IsKeyDown(KEY_A)) left(deltaTime);
    if (IsKeyDown(KEY_D)) right(deltaTime);

    Vector2 mousePos = GetMousePosition();
    updateRotation(mousePos);
}
