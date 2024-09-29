#include "PlayerProj.h"
#include "raymath.h"

// Constructor and destructor
PlayerProj::PlayerProj(Vector2 pos, Vector2 speed_raw) :Projectiles(pos, speed_raw, 15) , active(true) {
    Vector2 direction = {0,0};
    direction.x = speed_raw.x* (ProjSetSpeed/Vector2Length(speed_raw));
    direction.y = speed_raw.y* (ProjSetSpeed/Vector2Length(speed_raw));
    this->proj_speed = direction;
}

// Destructor
PlayerProj::~PlayerProj() {}

// Make sure you have implemented all virtual methods
void PlayerProj::setProjDamage(int damage)      { this->proj_damage = damage; }
void PlayerProj::setProjSpeed(Vector2 speed)    { this->proj_speed = speed; }
void PlayerProj::setProjPos(Vector2 pos)        { this->proj_pos = pos; }

//getter
bool PlayerProj::isActive() const {
    return active;
}

//Collision
bool PlayerProj::checkEdgeCollision() {
    if (proj_pos.x < 0 || proj_pos.x > GetScreenWidth() ||
        proj_pos.y < 0 || proj_pos.y > GetScreenHeight()) {
        active = false; 
        return true;    
    }
    return false;
}

bool PlayerProj::EnemyCollisionCheck(Vector2 enemy_pos, Vector2 enemy_bounding) {
    if (!active) return false;

    Vector2 relativePos = Vector2Subtract(proj_pos, enemy_pos);
    float normX = relativePos.x / (enemy_bounding.x / 2);
    float normY = relativePos.y / (enemy_bounding.y / 2);
    
    bool insideEllipse = (normX * normX + normY * normY <= 1.0f);
    if (insideEllipse) {
        active = false;
        return true;
    }

    float angle = atan2f(relativePos.y, relativePos.x);
    float ellipseX = (enemy_bounding.x / 2) * cosf(angle);
    float ellipseY = (enemy_bounding.y / 2) * sinf(angle);

    float dist_x = relativePos.x - ellipseX;
    float dist_y = relativePos.y - ellipseY;
    float distance = sqrtf(dist_x * dist_x + dist_y * dist_y);
    return distance < (lineThickness);
}

// Update and Render
void PlayerProj::update(float deltaTime) {
    proj_pos.x += proj_speed.x * deltaTime;
    proj_pos.y += proj_speed.y * deltaTime;

    if (checkEdgeCollision()) {
        active = false;
    }
}

void PlayerProj::draw() {
    Vector2 ProjEnd = {
        proj_pos.x + proj_speed.x * (ProjLength / Vector2Length(proj_speed)),
        proj_pos.y + proj_speed.y * (ProjLength / Vector2Length(proj_speed))
    };
    DrawLineEx(proj_pos, ProjEnd, lineThickness, PlayerProjCol);
}