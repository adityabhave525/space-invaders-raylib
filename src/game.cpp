#include "game.hpp"
// #include <iostream>

Game::Game()
{
    obstacles = CreateObstacles();
}

Game::~Game()
{
}

void Game::Update()
{
    for (auto &laser : spaceship.lasers)
    {
        laser.Update();
    }

    DeleteInactiveLasers();
    // std::cout << "Vector Size: " << spaceship.lasers.size() << '\n';
}

void Game::Draw()
{
    spaceship.Draw();

    for (auto &laser : spaceship.lasers)
    {
        laser.Draw();
    }

    for (auto &obstacle : obstacles)
    {
        obstacle.Draw();
    }
}

void Game::HandleInput()
{
    if (IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight();
    }
    else if (IsKeyDown(KEY_SPACE))
    {
        spaceship.FireLaser();
    }
}

void Game::DeleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (!it->active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacle_width = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacle_width)) / 5;

    for (int i = 0; i < 4; i++)
    {
        float offset_x = (i + 1) * gap + i * obstacle_width;
        obstacles.push_back(Obstacle({offset_x, float(GetScreenHeight() - 100)}));
    }

    return obstacles;
}
