// SaveLoad.cpp
#include "SaveLoad.h"
#include <fstream>
#include <iostream>

void saveGameState(const Player& player, const std::vector<std::unique_ptr<Asteroids>>& asteroids, 
                   const ScoutAlien& scout, const std::vector<PlayerProj>& projectiles, 
                   float timeAlive, const std::string& fileName) {
    std::ofstream file(fileName);

    if (!file) {
        std::cerr << "Unable to open save file!" << std::endl;
        return;
    }

    // Save player state
    Vector2 playerPos = player.getPLPos();
    file << "# Player\n";
    file << playerPos.x << " " << playerPos.y << " " << player.getPLHealth() << "\n";

    // Save asteroids
    file << "# Asteroids\n";
    file << asteroids.size() << "\n";
    for (const auto& asteroid : asteroids) {
        Vector2 asteroidPos = asteroid->getEnemyPos();
        Vector2 asteroidSpeed = asteroid->getEnemySpeed();
        int asteroidHealth = asteroid->getEnemyHealth();
        file << asteroidPos.x << " " << asteroidPos.y << " " << asteroidSpeed.x << " " 
             << asteroidSpeed.y << " " << asteroidHealth << "\n";
    }

    // Save ScoutAlien state
    Vector2 scoutPos = scout.getEnemyPos();
    file << "# ScoutAlien\n";
    file << scoutPos.x << " " << scoutPos.y << " " << scout.getBoolActive() << "\n";

    // Save projectiles
    file << "# Projectiles\n";
    file << projectiles.size() << "\n";
    for (const auto& proj : projectiles) {
        Vector2 projPos = proj.getProjPos();
        Vector2 projSpeed = proj.getProjSpeed();
        file << projPos.x << " " << projPos.y << " " << projSpeed.x << " " << projSpeed.y << "\n";
    }

    // Save game time
    file << "# TimeAlive\n";
    file << timeAlive << "\n";

    file.close();
}

void loadGameState(Player& player, std::vector<std::unique_ptr<Asteroids>>& asteroids, 
                   ScoutAlien& scout, std::vector<PlayerProj>& projectiles, 
                   float& timeAlive, const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file) {
        std::cerr << "No save file found!" << std::endl;
        return;
    }

    std::string line;

    // Load player state
    file >> line;  // skip "# Player"
    Vector2 playerPos;
    int playerHealth;
    file >> playerPos.x >> playerPos.y >> playerHealth;
    player.setPLHealth(playerHealth);
    player.setPLSpeed(playerPos);

    // Load asteroids
    file >> line;  // skip "# Asteroids"
    size_t numAsteroids;
    file >> numAsteroids;
    asteroids.clear();
    for (size_t i = 0; i < numAsteroids; ++i) {
        Vector2 pos, speed;
        int health;
        file >> pos.x >> pos.y >> speed.x >> speed.y >> health;
        auto newAsteroid = std::make_unique<Asteroids>(pos, speed);
        newAsteroid->setEnemyHealth(health);
        asteroids.push_back(std::move(newAsteroid));
    }

    // Load ScoutAlien state
    file >> line;  // skip "# ScoutAlien"
    Vector2 scoutPos;
    bool scoutActive;
    file >> scoutPos.x >> scoutPos.y >> scoutActive;
    scout.setEnemyPos(scoutPos);
    scout.setBoolActive(scoutActive);

    // Load projectiles
    file >> line;  // skip "# Projectiles"
    size_t numProjectiles;
    file >> numProjectiles;
    projectiles.clear();
    for (size_t i = 0; i < numProjectiles; ++i) {
        Vector2 pos, speed;
        int damage;
        file >> pos.x >> pos.y >> speed.x >> speed.y >> damage;
        projectiles.emplace_back(pos, speed, damage);
    }

    // Load game time
    file >> line;  // skip "# TimeAlive"
    file >> timeAlive;

    file.close();
}
