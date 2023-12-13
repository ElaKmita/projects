#pragma once

#include <raylib.h>
#include "ProjectVariables.h"

class Obstacle
{
public:
    Vector2 positionUpper, positionLower;
    float span;

    Obstacle();                                     
    Obstacle(float posX, float posY, float span);
    void draw();        // draw obstacle
    void update();      // causes simultion of the movement
};

