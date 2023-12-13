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

    void keyPressed(int direction);                 // detect and react if key is pressed
    void gameOver();                    
    void checkCollisionWithEdges();
    void checkCollisionWithObstacles(Obstacle* obstacle);
    void checkCollisionWithFood(Food* food, int& tableElement);
    void resetObstacle();
    void resetFood();                             
    void createNewObstacle();
    void deleteVanishedObstacle();                  // delete obstacle if vanishes from the window
    void createNewFood();
    void deleteVanishedFood();                      // delete food if disappears from the window
    void deleteFood(Food* food, int& tableElement); // delete food if is eaten by the unicorn
    void addPoint(Obstacle* obstacle);             
    void setLevel(int score);
};
