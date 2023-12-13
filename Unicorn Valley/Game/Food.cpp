#include "Food.h"

Food::Food(float x, float y, Texture2D textureCake, Texture2D textureLollipop)
{
    if (GetRandomValue(0, 3) == 0)
    {
        //texture = LoadTexture("D:\\GIT - priv\\CPP\\MyGame\\Game\\cake.png");
        texture = textureCake;
        type = 1;   // cake
    }
    else
    {
        texture = textureLollipop;
        //texture = LoadTexture("D:\\GIT - priv\\CPP\\MyGame\\Game\\lollipop.png");
        type = 2;   // lollipop
    }
    position = { x, y };
}

Food::~Food()
{
    //UnloadTexture(texture);
}

void Food::draw()
{
    DrawTexture(texture, position.x, position.y, WHITE);
    //DrawCircle(position.x, position.y, cellSize / 2, PINK);
}

void Food::update()
{
    position.x -= shift;
}