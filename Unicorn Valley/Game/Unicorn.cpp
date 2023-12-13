#include "Unicorn.h"

Unicorn::Unicorn()
{
    textureDown = LoadTexture(".\\Graphics\\unicorn_down.png");         // load image of unicorn flying down
    textureUp = LoadTexture(".\\Graphics\\unicorn_up.png");             // load image of unicorn flying up
    direction = initialDirection;                                       // number of cells by which the unicorn moves in the Y-axis
    acceleration = initialAcceleration;                                                   
    position = { (float)cellX * cellSize, (float)cellY * cellSize };    // start position for the unicorn
}

Unicorn::~Unicorn()
{
    UnloadTexture(textureDown);
    UnloadTexture(textureUp);
}

void Unicorn::draw()
{
    if (direction >= 0)     // unicorn is moving down - use textureDown
    {
        DrawTexture(textureDown, position.x, position.y, WHITE);
    }
    else                    // unicorn is moving up - use textureUp
    {
        DrawTexture(textureUp, position.x, position.y, WHITE);
    }
}

void Unicorn::update()
{
    position.y += direction * acceleration;     // change position of the unicorn
    acceleration *= 1.01;                       // increase acceleration 
}

void Unicorn::reset()                           // reset to initial values
{
    direction = initialDirection;
    acceleration = initialAcceleration;
    position = { (float)cellX * cellSize, (float)cellY * cellSize };
}