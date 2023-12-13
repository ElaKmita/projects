#include "Game.h"

Game::Game()
{
    textureCake = LoadTexture(".\\Graphics\\cake.png");
    textureLollipop = LoadTexture(".\\Graphics\\lollipop.png");
    spacePressed = true;
    score = 0;
    running = true;
    initialVariables();
    level = 0;
}

Game::~Game()
{
    UnloadTexture(textureCake);
    UnloadTexture(textureLollipop);
}

void Game::keyPressed(int direction)
{
    unicorn.direction = direction;
    unicorn.acceleration = 1;
    running = true;            // game is running again if user press KEY
}

void Game::GameOver()
{
    spacePressed = false;
    unicorn.reset();
    resetObstacle();
    resetFood();
    initialVariables();
    level = 0;
}

void Game::checkCollisionWithEdges()
{
    if (unicorn.position.y + unicornSize >= windowHeight || unicorn.position.y <= 0)
    {
        GameOver();
        running = false;
    }
}

void Game::checkCollisionWithObstacles(Obstacle* obstacle)
{
    if (unicorn.position.x + unicornSize >= obstacle->positionUpper.x && unicorn.position.x + unicornSize <= obstacle->positionUpper.x + obstacleWidth)
    {
        if (unicorn.position.y <= obstacle->positionUpper.y || unicorn.position.y >= obstacle->positionLower.y - unicornSize)
        {
            GameOver();
            running = false;
            return;
        }
    }
}

void Game::checkCollisionWithFood(Food* food, int& tableElement)
{
    int unicornFront = unicorn.position.x + unicornSize;
    int unicornTop = unicorn.position.y;
    int unicornBottom = unicorn.position.y + unicornSize;
    int foodBack, foodFront, foodTop, foodBottom;
    int points;

    if (food->type == 1)
    {
        // Cake
        foodBack = food->position.x;
        foodFront = food->position.x + cellSize;
        foodTop = food->position.y;
        foodBottom = food->position.y + cellSize;
        points = 3;
    }
    else
    {
        // Lollipop
        // unicornSize is the same as Lollipop size
        foodBack = food->position.x;
        foodFront = food->position.x + unicornSize;
        foodTop = food->position.y;
        foodBottom = food->position.y + unicornSize;
        points = 1;
    }

    if (unicornFront >= foodBack && unicornFront <= foodFront)
    {
        if ((unicornTop <= foodBottom && unicornTop >= foodTop) || (unicornBottom <= foodBottom && unicornBottom >= foodTop) || (unicornBottom <= foodTop && unicornBottom >= foodBottom) || (unicornTop <= foodTop && unicornTop >= foodBottom))
        {
            deleteRainbow(food, tableElement);
            score += points;
            setLevel(score);
        }
    }
}

void Game::resetObstacle()
{
    if (!obstacles.empty())
    {
        for (auto p = obstacles.begin(); p != obstacles.end(); p++)
        {
            delete* p;
        }
        obstacles.clear();
    }
    obstacles.push_back(new Obstacle(15, 12, 6));
    obstacles.push_back(new Obstacle(28, 16, 6));
}

void Game::resetFood()
{
    if (!foods.empty())
    {
        for (auto p = foods.begin(); p != foods.end(); p++)
        {
            delete* p;
        }
        foods.clear();
    }
}

void Game::createNewObstacle()
{
    if (obstacles.back()->positionUpper.x < minObstaclesSpace)
    {
        obstacles.push_back(new Obstacle());
        if (abs(obstacles.back()->positionUpper.y - (obstacles[obstacles.size() - 2])->positionUpper.y) >= 13 * cellSize)
        {
            delete obstacles.back();
            obstacles.pop_back();
        }
        else
        {
            createNewFood();
        }
    }
}

void Game::deleteVanishedObstacle()
{
    if ((obstacles[0]->positionUpper.x + obstacleWidth) <= 0)
    {
        delete obstacles[0];
        obstacles.erase(obstacles.begin());
    }
}

void Game::createNewFood()
{
    if (GetRandomValue(0, 1) == 0)      //probability: 50%
    {
        float x = obstacles.back()->positionUpper.x + obstacleWidth + GetRandomValue(2, 3) * cellSize;
        float y = obstacles.back()->positionUpper.y + GetRandomValue(-1, 1) * cellSize;
        foods.push_back(new Food(x, y, textureCake, textureLollipop));
    }
}

void Game::deleteVanishedRainbow()
{
    if ((foods[0]->position.x) <= 0)
    {
        delete foods[0];
        foods.erase(foods.begin());
    }
}

void Game::deleteRainbow(Food* rainbow, int& tableElement)
{
    delete rainbow;
    foods.erase(foods.begin() + tableElement);
}

void Game::addPoint(Obstacle* obstacle)
{
    if (obstacle->positionUpper.x + obstacleWidth <= unicorn.position.x && obstacle->positionUpper.x + obstacleWidth > unicorn.position.x - shift)
    {
        score++;
        setLevel(score);
    }
}

void Game::setLevel(int score)
{
    if (score >= 10 && level == 0)   // 10
    {
        level = 1;
        minY = 8;
        maxY = 18;
        minSpan = 6;
        maxSpan = 7;
    }
    else if (score >= 25 && level == 1) 
    {
        level = 2;
        minY = 4;
        maxY = 20;
        minSpan = 5;    
        maxSpan = 6;    
    }
    else if (score >= 40 && level == 2)
    {
        level = 3;
        minY = 0;
        maxY = 24;
        minSpan = 4;
        maxSpan = 6;
    }
}