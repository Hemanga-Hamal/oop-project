#include "Player.h"
#include "DynamicPlayerProj.h"
#include "raymath.h"
#include <cmath>

Player::Player(Vector2 pos, int health) : pl_pos(pos), pl_health(health), activeBulletCount(0) {}

Player::~Player() {
    // Clean up dynamically allocated projectiles
    for (DynamicPlayerProj* proj : projectiles) {
        delete proj;
    }
}

// Setters
void Player::setPLHealth(int health) { pl_health = health; }
void Player::setPLSpeed(const Vector2& speed) { pl_speed = speed; }
void Player::setRotation(float rotation) { pl_rot = rotation; }

// Getters
Vector2 Player::getPLPos() const { return pl_pos; }
Vector2 Player::getPLSpeed() const { return pl_speed; }
Vector2 Player::getBoundingBox() const { return pl_BoundingBox; }
Vector2 Player::getPlayershotDir() const { return v1; }
int Player::getActiveBulletCount() const { return activeBulletCount; }
int Player::getPLHealth() const { return pl_health; }
float Player::getRotation() const { return pl_rot; }
float Player::getAccelerationRate() const { return accelerationRate; }
float Player::getfriction() const { return friction; }

void Player::movement(float deltaTime) {
    // Reset acceleration each frame
    pl_acceleration = { 0.0f, 0.0f };

    // Apply acceleration based on key presses
    if (IsKeyDown(KEY_W)) pl_acceleration.y -= accelerationRate;
    if (IsKeyDown(KEY_S)) pl_acceleration.y += accelerationRate;
    if (IsKeyDown(KEY_A)) pl_acceleration.x -= accelerationRate;
    if (IsKeyDown(KEY_D)) pl_acceleration.x += accelerationRate;

    // Update speed based on acceleration
    pl_speed.x += pl_acceleration.x * deltaTime;
    pl_speed.y += pl_acceleration.y * deltaTime;

    // Apply friction
    pl_speed.x *= (1.0f - friction);
    pl_speed.y *= (1.0f - friction);

    // Clamp speed to maximum
    float currentSpeed = sqrtf(pl_speed.x * pl_speed.x + pl_speed.y * pl_speed.y);
    if (currentSpeed > maxSpeed) {
        float scale = maxSpeed / currentSpeed;
        pl_speed.x *= scale;
        pl_speed.y *= scale;
    }

    // Move the player
    pl_pos.x += pl_speed.x * deltaTime;
    pl_pos.y += pl_speed.y * deltaTime;

    // Wrap around screen edges
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    if (pl_pos.x < 0) pl_pos.x = screenWidth;
    if (pl_pos.x > screenWidth) pl_pos.x = 0;
    if (pl_pos.y < 0) pl_pos.y = screenHeight;
    if (pl_pos.y > screenHeight) pl_pos.y = 0;
}

// Get projectiles
std::vector<DynamicPlayerProj*>& Player::getProjectiles() { return projectiles; }

void Player::decrementBulletCount() {
    if (activeBulletCount > 0) {
        --activeBulletCount;
    }
    activeBulletCount = std::max(activeBulletCount, 0);
}

void Player::shoot() {
    if (pl_shootTimeRemaining <= 0.0f) {
        pl_shootTimeRemaining = pl_shootdelay;
        if (projectiles.size() < static_cast<std::vector<DynamicPlayerProj*>::size_type>(maxProjectiles)) {
            Vector2 direction = { cosf(pl_rot - (float)PI / 2.0f), sinf(pl_rot - (float)PI / 2.0f) };
            DynamicPlayerProj* newProj = new DynamicPlayerProj(pl_pos, direction); // Create new projectile dynamically
            projectiles.push_back(newProj);
            activeBulletCount++;
        }
    }
}

// Collision logic
bool Player::checkColEnemy(Vector2 enemyPos, Vector2 enemyBounding) {
    Vector2 relativePos = Vector2Subtract(enemyPos, pl_pos);
    Vector2 rotatedPos = Vector2Rotate(relativePos, -pl_rot);

    float normX = rotatedPos.x / pl_BoundingBox.x;
    float normY = rotatedPos.y / pl_BoundingBox.y;
    bool insideEllipse = (normX * normX + normY * normY <= 1.0f);
    
    if (insideEllipse) { return true; }

    float angle = atan2f(rotatedPos.y, rotatedPos.x);
    float ellipseX = pl_BoundingBox.x * cosf(angle);
    float ellipseY = pl_BoundingBox.y * sinf(angle);
    float dist_x = rotatedPos.x - ellipseX;
    float dist_y = rotatedPos.y - ellipseY;
    float distance = sqrtf(dist_x * dist_x + dist_y * dist_y);

    return distance < enemyBounding.x || distance < enemyBounding.y;
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
    v1 = { pl_pos.x, pl_pos.y - size };
    v2 = { pl_pos.x - size / 2, pl_pos.y + size / 2 + 2 };
    v3 = { pl_pos.x + size / 2, pl_pos.y + size / 2 + 2 };
    Vector2 center = pl_pos;

    v1 = Vector2Rotate(Vector2Subtract(v1, center), pl_rot);
    v1 = Vector2Add(v1, center);
    v2 = Vector2Rotate(Vector2Subtract(v2, center), pl_rot);
    v2 = Vector2Add(v2, center);
    v3 = Vector2Rotate(Vector2Subtract(v3, center), pl_rot);
    v3 = Vector2Add(v3, center);

    pl_colour = (pl_flashRedTimeRemaining > 0) ? RED : BLUE;
    DrawTriangle(v1, v2, v3, pl_colour);

    // Draw projectiles
    for (DynamicPlayerProj* proj : projectiles) {
        proj->draw();  // Call draw on each dynamically allocated projectile
    }
}

// Update
void Player::update(float deltaTime) {
    // Movement
    movement(deltaTime);

    // Call the shoot method when the shoot key is pressed
    if (IsKeyDown(KEY_SPACE)) {
        shoot();
    }

    // Model rotation
    Vector2 mousePos = GetMousePosition();
    updateRotation(mousePos);

    // Take damage color swap
    if (pl_flashRedTimeRemaining > 0.0f) {
        pl_flashRedTimeRemaining -= deltaTime;
    }

    // Shooting delay countdown
    if (pl_shootTimeRemaining > 0.0f) {
        pl_shootTimeRemaining -= deltaTime;
    }

    // Update projectiles and remove inactive ones
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        (*it)->update(deltaTime);  // Call update on each projectile
        if (!(*it)->isActive()) {
            delete *it;  // Delete inactive projectile
            it = projectiles.erase(it);  // Erase pointer from vector
            activeBulletCount--;
        } else {
            ++it;
        }
    }
}
