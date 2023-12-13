#pragma once

#include <raylib.h>
#include "ProjectVariables.h"

class Food
{
public:
    Vector2 position;
    Texture2D texture;

    int type;

    Food(float x, float y, Texture2D textureCake, Texture2D textureLollipop);
    ~Food();
    void draw();
    void update();
    
};

