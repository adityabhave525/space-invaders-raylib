#include <raylib.h>
#include "game.hpp"
#include <string>

std::string FormatWithLeadingZeros(int number, int width)
{
    std::string number_text = std::to_string(number);
    int leading_zeros = width - number_text.length();
    number_text = std::string(leading_zeros, '0') + number_text;
    return number_text;
}

int main()
{
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50;
    int window_width = 750;
    int window_height = 700;

    InitWindow(window_width + offset, window_height + 2 * offset, "Space Invaders Raylib");
    InitAudioDevice();

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceship_image = LoadTexture("Graphics/spaceship.png");

    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);

        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);
        if (game.run)
        {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        }
        else
        {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }

        float x = 50.0;
        for (int i = 0; i < game.lives; i++)
        {
            DrawTextureV(spaceship_image, {x, 745}, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string score_text = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, score_text.c_str(), {50, 40}, 34, 2, yellow);

        DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
        std::string high_score_text = FormatWithLeadingZeros(game.high_score, 5);
        DrawTextEx(font, high_score_text.c_str(), {655, 40}, 34, 2, yellow);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
}