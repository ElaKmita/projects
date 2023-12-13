#include "Food.h"

Food::Food(float x, float y, Texture2D textureCake, Texture2D textureLollipop)
{
    if (GetRandomValue(0, 3) == 0)
    {
        texture = textureCake;
        type = 1;   // cake
    }
    else
    {
        texture = textureLollipop;
        type = 2;   // lollipop
    }
    position = { x, y };
}

void Food::draw()
{
    DrawTexture(texture, position.x, position.y, WHITE);
}

void Food::update()
{
    position.x -= shift;        // movement simulation
}