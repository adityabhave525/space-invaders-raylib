#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
#include <iostream>

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
    std::vector<Alien> CreateAliens();
    void MoveAliens();
    void MoveDownAliens(int distance);
    void AlienShootLaser();
    void CheckForCollisions();
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    int aliens_direction;
    std::vector<Laser> alien_lasers;
    constexpr static float alien_laser_shoot_interval = 0.35;
    float time_last_alien_fired;
    MysteryShip mysteryship;
    float mystery_ship_spawn_interval;
    float time_last_spawn;
};