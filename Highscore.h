#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Highscore {
    // Variables
    std::string name;
    float score;
    
    // Overloading of the < operator
    bool operator<(const Highscore& other) const {
        return score > other.score; // Sorts in descending order
    }
};

const std::string fileName = "highscores.txt"; // Declares automated file creation name as "highscores.txt"

void createFile(const std::string& fileName); // Creates a file if it does not exist
void loadHighScores(std::vector<Highscore>& highscores, const std::string& fileName); // Loads high scores from the file from a vector of scores
void saveHighScore(const Highscore& newScore, const std::string& fileName); // Saves the high score to the file and to the vector of scores
void displayHighScores(const std::vector<Highscore>& highscores); // References the vector of scores

// Getter function to get the player's name from the file
std::string getPlayerName();

#endif