#include <raylib.h>
#include "game.hpp"

int main()
{
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50;
    int window_width = 750;
    int window_height = 700;

    InitWindow(window_width + offset, window_height + 2 * offset, "Space Invaders Raylib");

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceship_image = LoadTexture("Graphics/spaceship.png");

    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
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

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}