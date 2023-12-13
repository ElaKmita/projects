#include <raylib.h>

#ifndef PROJECT_VARIABLES_H
#define PROJECT_VARIABLES_H

// color 
extern Color backgroundColor;
extern Color obstaclesColor;

// window size
extern const int cellSize;
extern const int unicornSize;
extern const int cellCountWidth;
extern const int cellCountHeight;
extern const int offset;
extern const int windowWidth;
extern const int windowHeight;

extern double lastUpdateTime;

extern int minY;		// minimum Y value where upper obstacle can end (in cells)
extern int maxY;		// maximum Y value where upper obstacle can end (in cells)
extern int minSpan;		// minimum span between upper and lower obstacle (in cells)
extern int maxSpan;		// maximum span between upper and lower obstacle (in cells)
extern int shift;		// the value of movement while updating obstacles and food 

void initializeVariables();

extern const int obstacleWidth;
extern const int minObstaclesSpace;		// minimum space between two obstacles

#endif // !PROJECT_VARIABLES_H




