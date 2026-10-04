#include <raylib.h>

int main() 
{
    Color grey = {29,29,27,255};

    int window_width = 750;
    int window_height = 700;

    InitWindow(window_width, window_height, "Space Invaders Raylib");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(grey);
        
        EndDrawing();
    }

    CloseWindow();
}