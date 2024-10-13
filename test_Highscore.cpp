#include <iostream>
#include <vector>
#include <algorithm>
#include "Highscore.h"
#include "raylib.h"
#include "raymath.h"
#include <memory>
#include <ctime>
#include <cassert>

// Struct to store test results
struct TestResult {
    std::string testName;
    bool passed;
};

// Function to draw test results on screen
void drawTestResults(const TestResult results[], int count) {
    int yPosition = 20;  // Starting Y position for drawing text

    for (int i = 0; i < count; i++) {
        std::string message = results[i].testName + ": " + (results[i].passed ? "PASSED" : "FAILED");
        Color textColor = results[i].passed ? GREEN : RED;
        DrawText(message.c_str(), 20, yPosition, 20, textColor);
        yPosition += 30;  // Move down for the next result
    }
}

// Test functions
bool testCreateFile() {
    createFile("test.txt");
    std::ifstream file("test.txt");
    return file.is_open();
}

bool testLoadHighscore() {
    std::vector<Highscore> highscores;
    loadHighScores(highscores, "test.txt");
    return highscores.size() > 0;
}

bool testSaveHighscore() {
    Highscore newScore = {"Test", 100.0f};
    saveHighScore(newScore, "test.txt");
    std::vector<Highscore> highscores;
    loadHighScores(highscores, "test.txt");
    return highscores.size() > 0;
}

bool testDisplayHighscore() {
    std::vector<Highscore> highscores;
    loadHighScores(highscores, "test.txt");
    displayHighScores(highscores);
    return true;
}

// Main function
int main() {
    // Initialize Raylib window
    InitWindow(800, 600, "Highscore Test Results");
    SetTargetFPS(60);

    // Run the tests and store the results
    TestResult results[] = {
        {"File Creation", testCreateFile()},
        {"Score Saving", testSaveHighscore()},
        {"File Loading", testLoadHighscore()},
        {"Display Scores", testDisplayHighscore()}
    };
    int testCount = sizeof(results) / sizeof(results[0]);

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the test results
        drawTestResults(results, testCount);

        EndDrawing();
    }

    // Close Raylib window
    CloseWindow();

    return 0;
}