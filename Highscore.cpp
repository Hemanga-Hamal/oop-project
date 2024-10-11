#include "Highscore.h"
#include <fstream> // IFSTREAM - READS, OFSTREAM - CREATES AND WRITES, FSTREAM - BOTH
#include <algorithm>
#include "raylib.h"
#include <iostream>
#include <ios>
#include <unistd.h>

void createFile(const std::string& fileName) {
    std::ofstream file(fileName, std::ios::app);
    if (file) { // Checks to see if the file can be opened successfully
        file.close();
    } else {
        std::cerr << "Error creating file: " << fileName << std::endl;
    }
}

void loadHighScores(std::vector<Highscore>& highscores, const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::ofstream createFile(fileName);
        createFile.close();
        return;
    }

    Highscore entry;
    while (file >> entry.name >> entry.score) { // Reads the name as the first input and score as the second input from the file
        highscores.push_back(entry); // Appends the name and score to the vector
    }
}

void saveHighScore(const Highscore& newScore, const std::string& fileName) {
    std::ofstream file(fileName, std::ios::app);
    if (file.is_open()) {
        file << newScore.name << " " << newScore.score << "\n"; // Appends the name and score to the file
    }
}

void displayHighScores(const std::vector<Highscore>& highscores) {
    for (size_t i = 0; i < highscores.size(); ++i) {
        DrawText(TextFormat("%s: %.2f", highscores[i].name.c_str(), highscores[i].score), 10, 150 + 20 * i, 20, DARKGRAY); // Displays the name and score on the screen
    }
}

std::string getPlayerName() {
    std::string name;
    bool firstChar = true;
    while (name.size() < 3) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Enter your name (3 Characters): ", 250, 360, 20, DARKGRAY);
        // Check for character input
        for (char ch = 'A'; ch <= 'Z'; ++ch) {
            if (IsKeyPressed((int)ch)) {
                name += ch; // Append uppercase character
            }
        }
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (IsKeyPressed((int)ch)) {
                name += toupper(ch); // Append uppercase character
            }
        }
        // Handle backspace
        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!name.empty()) {
                name.pop_back(); // Removes last character
            }
        }
        if (firstChar) {
            name.pop_back();
            firstChar = false;
        }
        // Draw the current input
        DrawText(name.c_str(), 250, 400, 20, DARKGRAY);
        EndDrawing();
    }
    return name;
}