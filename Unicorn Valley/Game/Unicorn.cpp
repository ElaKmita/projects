#include "Unicorn.h"

Unicorn::Unicorn()
{
    textureDown = LoadTexture(".\\Graphics\\unicorn_down.png");
    textureUp = LoadTexture(".\\Graphics\\unicorn_up.png");
    direction = 2;
    acceleration = 1;
    //position = { 0, 0 };
    position = { (float)cellX * cellSize, (float)cellY * cellSize };
}

Unicorn::~Unicorn()
{
    UnloadTexture(textureDown);
    UnloadTexture(textureUp);
}

void Unicorn::draw()
{
    if (direction >= 0)
    {
        DrawTexture(textureDown, position.x, position.y, WHITE);
    }
    else
    {
        DrawTexture(textureUp, position.x, position.y, WHITE);
    }
    //DrawRectangle(position.x, position.y, cellSize, cellSize, BLACK);
}

void Unicorn::update()
{
    position.y += direction * acceleration;
    acceleration *= 1.01;
}

void Unicorn::reset()
{
    direction = 2;
    acceleration = 1;
    position = { (float)cellX * cellSize, (float)cellY * cellSize };
}