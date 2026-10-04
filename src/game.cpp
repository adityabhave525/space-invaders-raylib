#include "game.hpp"
// #include <iostream>

Game::Game()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliens_direction = 1;
    time_last_alien_fired = 0.0;
    time_last_spawn = 0.0;
    mystery_ship_spawn_interval = GetRandomValue(10, 20);
}

Game::~Game()
{
    Alien::UnloadImages();
}

void Game::Update()
{
    double current_time = GetTime();
    if (current_time - time_last_spawn > mystery_ship_spawn_interval)
    {
        mysteryship.Spawn();
        time_last_spawn = GetTime();
        mystery_ship_spawn_interval = GetRandomValue(10, 20);
    }

    for (auto &laser : spaceship.lasers)
    {
        laser.Update();
    }

    MoveAliens();

    AlienShootLaser();

    for (auto &laser : alien_lasers)
    {
        laser.Update();
    }

    DeleteInactiveLasers();
    mysteryship.Update();
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

    for (auto &alien : aliens)
    {
        alien.Draw();
    }

    for (auto &laser : alien_lasers)
    {
        laser.Draw();
    }

    mysteryship.Draw();
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

    for (auto it = alien_lasers.begin(); it != alien_lasers.end();)
    {
        if (!it->active)
        {
            it = alien_lasers.erase(it);
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

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 11; col++)
        {

            int alien_type;

            if (row == 0)
            {
                alien_type = 3;
            }
            else if (row == 1 || row == 2)
            {
                alien_type = 2;
            }
            else
            {
                alien_type = 1;
            }

            float x = 75 + col * 55;
            float y = 110 + row * 55;

            aliens.push_back(Alien(alien_type, {x, y}));
        }
    }

    return aliens;
}

void Game::MoveAliens()
{
    for (auto &alien : aliens)
    {
        if (alien.position.x + alien.alien_images[alien.type - 1].width > GetScreenWidth())
        {
            aliens_direction = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 0)
        {
            aliens_direction = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliens_direction);
    }
}

void Game::MoveDownAliens(int distance)
{
    for (auto &alien : aliens)
    {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double current_time = GetTime();

    if (current_time - time_last_alien_fired >= alien_laser_shoot_interval && !aliens.empty())
    {

        int random_index = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[random_index];
        alien_lasers.push_back(
            Laser(
                {alien.position.x + alien.alien_images[alien.type - 1].width / 2,
                 alien.position.y + alien.alien_images[alien.type - 1].height},
                6));
        time_last_alien_fired = GetTime();
    }
}
