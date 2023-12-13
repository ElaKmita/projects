#include "Obstacle.h"

Obstacle::Obstacle()
{
    float posY = GetRandomValue(minY, maxY) * cellSize;         // set random available Y position for upper obstacle
    float posX = windowWidth + GetRandomValue(0, 3) * cellSize; // set random available X position for obstacles
    span = GetRandomValue(minSpan, maxSpan) * cellSize;         // set random value of the span between lower an upper obstacle
    positionUpper = { posX, posY };                             // left bottom node of upper obstacle
    positionLower = { posX, posY + span };                      // left top node of lower obstacle
}

Obstacle::Obstacle(float posX, float posY, float span)
{
    this->span = span;
    positionUpper = { posX * cellSize, posY * cellSize };               // left bottom node of upper obstacle
    positionLower = { posX * cellSize, (posY + span) * cellSize };      // left top node of lower obstacle
}

void Obstacle::draw()
{
    DrawRectangle(positionUpper.x, 0, obstacleWidth, positionUpper.y, obstaclesColor);     // upper obstacle
    DrawRectangle(positionUpper.x, positionLower.y, obstacleWidth, windowHeight - positionLower.y, obstaclesColor); // lower obstacle
}

void Obstacle::update()
{
    positionUpper.x -= shift;           // simulation of the movement for upper obstacle
    positionLower.x -= shift;           // simulation of the movement for lower obstacles
}