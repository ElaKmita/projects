#include <raylib.h>

#ifndef PROJECT_VARIABLES_H
#define PROJECT_VARIABLES_H

// color 
extern Color backgroundColor;
extern Color obstaclesColor;

// window size
extern const int cellSize;
extern const int unicornSize;
extern const int CellCountWidth;
extern const int CellCountHeight;
extern const int offset;
extern const int windowWidth;
extern const int windowHeight;

extern double lastUpdateTime;

extern int minY;
extern int maxY;
extern int minSpan;
extern int maxSpan;
extern int shift;

void initialVariables();

/*
extern const int minY;		
extern const int maxY;
extern const int minSpan;
extern const int maxSpan;
extern const int shift;
*/
extern const int obstacleWidth;
extern const int minObstaclesSpace;

#endif // !PROJECT_VARIABLES_H




