#include "Obstacle.h"

Obstacle::Obstacle()
{
    float posY = GetRandomValue(minY, maxY) * cellSize;
    float posX = windowWidth + GetRandomValue(0, 3) * cellSize;
    span = GetRandomValue(minSpan, maxSpan) * cellSize;
    positionUpper = { posX, posY };                 // left bottom node
    positionLower = { posX, posY + span };          // left top node
}

Obstacle::Obstacle(float posX, float posY, float span)
{
    this->span = span;
    positionUpper = { posX * cellSize, posY * cellSize };               // left bottom node
    positionLower = { posX * cellSize, (posY + span) * cellSize };      // left top node
}

void Obstacle::draw()
{
    DrawRectangle(positionUpper.x, 0, obstacleWidth, positionUpper.y, obstaclesColor);     // lupper obstacle
    DrawRectangle(positionUpper.x, positionLower.y, obstacleWidth, windowHeight - positionLower.y, obstaclesColor);
}

void Obstacle::update()
{
    positionUpper.x -= shift;
    positionLower.x -= shift;
}