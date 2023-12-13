#pragma once

#include <vector>
#include "ProjectVariables.h"
#include "Obstacle.h"
#include "Food.h"
#include "Unicorn.h"

class Game {
public:
    bool running;
    Unicorn unicorn = Unicorn();
    std::vector<Obstacle*> obstacles;
    std::vector<Food*> foods;
    int score;
    bool spacePressed;
    Texture2D textureCake;
    Texture2D textureLollipop;
    int level;

    Game();
    ~Game();

    void keyPressed(int direction);
    void GameOver();
    void checkCollisionWithEdges();
    void checkCollisionWithObstacles(Obstacle* obstacle);
    void checkCollisionWithFood(Food* food, int& tableElement);
    void resetObstacle();
    void resetFood();
    void createNewObstacle();
    void deleteVanishedObstacle();
    void createNewFood();
    void deleteVanishedRainbow();
    void deleteRainbow(Food* rainbow, int& tableElement);
    void addPoint(Obstacle* obstacle);
    void setLevel(int score);
};
