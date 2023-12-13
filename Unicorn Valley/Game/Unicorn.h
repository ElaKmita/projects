#pragma once

#include <raylib.h>
#include "ProjectVariables.h"

class Unicorn
{
private:
    const int cellX = 5;        // 5th cell on x axis
    const int cellY = 10;       // 10th cell on y axin

public:
    Texture2D textureDown, textureUp;
    Vector2 position;
    float direction;
    float acceleration;

    Unicorn();                  // consructor - set initial values
    ~Unicorn();                 // destructor

    void draw();                // draw Unicorn
    void update();              // update causes simulation of the movement
    void reset();               // reset data to the initial values
};