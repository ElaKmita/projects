#include "ProjectVariables.h"

Color backgroundColor = { 255, 201, 244, 255 };
Color obstaclesColor = { 202, 44, 126, 255 };

const int cellSize = 40;			// each imaginary cell is 40x40 pixels
const int unicornSize = 80;			
const int cellCountWidth = 30;		// width consist of 30 imaginary cells
const int cellCountHeight = 30;		// height consist of 30 imaginary cells
const int offset = 4 * cellSize;	// offset for displaying points
const int windowWidth = cellSize * cellCountWidth;		
const int windowHeight = cellSize * cellCountHeight;

double lastUpdateTime = 0;

int minY = 10;				
int maxY = 15;  
int minSpan = 8;
int maxSpan = 10;
int shift = 3;

void initializeVariables()
{
	minY = 10;  
	maxY = 15;
	minSpan = 8;
	maxSpan = 10;
	shift = 3;
}

const int obstacleWidth = 4 * cellSize;
const int minObstaclesSpace = windowWidth - 12 * cellSize;
