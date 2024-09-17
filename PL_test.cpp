#include "raylib.h"
#include "Player.h"

int main() {
    //Intz
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Player Test");
    Player player(screenWidth / 2.0f, screenHeight / 2.0f, 100, {25.0f, 25.0f}, 10);
    SetTargetFPS(60);

    //GAME LOOP
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        player.update(deltaTime);

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        player.draw();
        DrawText("Player Test", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    //CLOSE
    CloseWindow();
    return 0;
}
