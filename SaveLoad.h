// SaveLoad.h
#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "Player.h"
#include "Asteroids.h"
#include "ScoutAlien.h"
#include "PlayerProj.h"
#include <vector>
#include <memory>
#include <string>

// Function to save game state
void saveGameState(const Player& player, const std::vector<std::unique_ptr<Asteroids>>& asteroids, 
                   const ScoutAlien& scout, const std::vector<PlayerProj>& projectiles, 
                   float timeAlive, const std::string& fileName);

// Function to load game state
void loadGameState(Player& player, std::vector<std::unique_ptr<Asteroids>>& asteroids, 
                   ScoutAlien& scout, std::vector<PlayerProj>& projectiles, 
                   float& timeAlive, const std::string& fileName);

#endif // SAVELOAD_H
