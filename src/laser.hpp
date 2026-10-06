#pragma once
#include <raylib.h>

class Laser
{
public:
    Laser(Vector2 position, int speed);
    void Draw();
    void Update();
    Rectangle getRect();
    bool active;

private:
    Vector2 position;
    int speed;
};