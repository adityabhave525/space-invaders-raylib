#include <raylib.h>
#include "game.hpp"

int main()
{
    Color grey = {29, 29, 27, 255};

    int window_width = 750;
    int window_height = 700;

    InitWindow(window_width, window_height, "Space Invaders Raylib");

    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}