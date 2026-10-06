#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class Spaceship
{
public:
    Spaceship();
    ~Spaceship();
    void Draw();
    void MoveLeft();
    void MoveRight();
    void FireLaser();
    Rectangle getRect();
    std::vector<Laser> lasers;

private:
    Texture2D image;
    Vector2 position;
    double last_fire_time;
};