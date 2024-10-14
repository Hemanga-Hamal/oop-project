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
    for (size_t i = 0; i < std::min(highscores.size(), static_cast<size_t>(10)); ++i) {
        std::string text = TextFormat("%s: %.1f", highscores[i].name.c_str(), highscores[i].score);
        int textWidth = MeasureText(text.c_str(), 20);
        DrawText(text.c_str(), 400 - textWidth / 2, 200 + 20 * i, 20, GRAY);
    }
}

std::string getPlayerName() {
    std::string name;
    bool showErrorMessage = false;
    bool firstChar = true;
    const std::string errorMessage = "Only letters are allowed!";

    while (name.size() < 3) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Enter your name (3 Characters): ", 400 - MeasureText("Enter your name (3 Characters): ", 20) / 2, 300 - 30, 20, GRAY);

        bool validInput = false;
        for (char ch = 'A'; ch <= 'Z'; ++ch) {
            if (IsKeyPressed((int)ch)) {
                name += ch;
                validInput = true;
                showErrorMessage = false;
            }
        }
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (IsKeyPressed((int)ch)) {
                name += toupper(ch);
                validInput = true;
                showErrorMessage = false;
            }
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (!name.empty()) {
                name.pop_back();
                showErrorMessage = false;
            }
        }

        if (!validInput) {
            for (int key = KEY_SPACE; key <= KEY_KP_EQUAL; ++key) {
                if (IsKeyPressed(key) && ((key < 'A' || key > 'Z') && (key < 'a' || key > 'z') && key != KEY_BACKSPACE)) {
                    showErrorMessage = true;
                    break;
                }
            }
        }

        if (firstChar) {
            name.pop_back();
            firstChar = false;
        }

        DrawText(name.c_str(), 400 - MeasureText(name.c_str(), 20) / 2, 300, 20, GRAY);

        if (showErrorMessage) {
            DrawText(errorMessage.c_str(), 400 - MeasureText(errorMessage.c_str(), 20) / 2, 350, 20, RED);
        }

        EndDrawing();
    }
    return name;
}