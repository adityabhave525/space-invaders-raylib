#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();

private:
    void DeleteInactiveLasers();
    std::vector<Obstacle> CreateObstacles();
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
};