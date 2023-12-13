#include <iostream>
#include <raylib.h>
#include <vector>

#include "ProjectVariables.h"
#include "Unicorn.h"
#include "Obstacle.h"
#include "Food.h"
#include "Game.h"

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(windowWidth, windowHeight + offset, "Unicorn Valley");
    SetTargetFPS(60);
    
    int elem;
    Game game = Game();
    game.resetObstacle();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);
        if (game.spacePressed)
        {
            DrawLineEx(Vector2{ 0, (float)windowHeight }, Vector2{ (float)windowWidth, (float)windowHeight }, 10, obstaclesColor);
            std::string text = TextFormat("Scores: %i", game.score);
            DrawText(text.c_str(), windowWidth - 7 * cellSize, windowHeight + cellSize, 50, BLACK);

            if (IsKeyPressed(KEY_UP))
            {
                game.keyPressed(-2);
            }
            if (IsKeyPressed(KEY_DOWN))
            {
                game.keyPressed(2);
            }

            game.unicorn.draw();

            for (Obstacle* obstacle : game.obstacles)
            {
                obstacle->draw();
            }

            if (game.running)
            {
                if (eventTriggered(0.01))
                {
                    game.unicorn.update();
                    for (Obstacle* obstacle : game.obstacles)
                    {
                        obstacle->update();
                        game.checkCollisionWithObstacles(obstacle);
                        game.addPoint(obstacle);
                    }

                    elem = 0;
                    for (Food* rainbow : game.foods)
                    {
                        rainbow->draw();
                        game.checkCollisionWithFood(rainbow, elem);
                        elem++;
                        rainbow->update();
                    }

                    if (!game.obstacles.empty())
                    {
                        game.createNewObstacle();
                        game.deleteVanishedObstacle();
                    }
                    if (!game.foods.empty())
                    {
                        game.deleteVanishedRainbow();
                    }
                    game.checkCollisionWithEdges();
                }
            }
        }
        else
        {
            std::string text = TextFormat("Scores: %i", game.score);
            DrawText(text.c_str(), windowWidth / 6, windowHeight / 3, 4 * cellSize, BLACK);
            DrawText("Press SPACE to continue...", windowWidth / 4 + cellSize, windowHeight/2 + 3*cellSize, cellSize, BLACK);
            if (IsKeyPressed(KEY_SPACE))
            {
                game.spacePressed = true;
            }
            if (game.spacePressed)
            {
                game.score = 0;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

