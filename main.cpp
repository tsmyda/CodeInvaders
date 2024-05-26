#include <raylib.h>
#include "Game.h"
#include "string"

int main()
{
    Color grey = Color{29, 29, 29, 255};
    int offset = 50;
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth+offset, screenHeight+2*offset, "Code Invaders");
    Font font = LoadFontEx("../fonts/monogram.ttf", 64, 0, 0);
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({10, 10, 830, 680}, 0.2f, 20, 2, GREEN);
        DrawLineEx({10, 620}, {840, 620}, 3, GREEN);
        Texture2D spaceshipImage = LoadTexture("../graphics/cpp.png");
        if (game.run) {
//            DrawTextEx(font, game.levels[game.level].c_str(), {650, 635}, 34, 2, GREEN);
            DrawTextEx(font, ("Level " + std::to_string(game.level)).c_str(), {650, 635}, 34, 2, GREEN);
        } else {
            DrawTextEx(font, "Game Over", {350, float(GetScreenHeight()/2)}, 34, 2, GREEN);
            DrawTextEx(font, "Press ENTER to restart", {250, float(GetScreenHeight()/2)+50}, 34, 2, GREEN);
        }
        float x = 50.0;
        for (int i=0; i<game.lives; i++) {
            DrawTextureV(spaceshipImage, {x, 630}, WHITE);
            x+=50;
        }
        DrawTextEx(font, "SCORE", {float(GetScreenWidth()/2-70), 620}, 34, 2, GREEN);
        std::string score = std::to_string(game.score);
        int leadingZeros = 5 - score.length();
        score = std::string(leadingZeros, '0') + score;
        DrawTextEx(font, score.c_str(), {float(GetScreenWidth()/2-70), 645}, 34, 2, GREEN);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
