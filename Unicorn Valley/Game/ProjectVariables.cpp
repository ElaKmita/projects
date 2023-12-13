#include "ProjectVariables.h"

Color backgroundColor = { 255, 201, 244, 255 };
Color obstaclesColor = { 202, 44, 126, 255 };

const int cellSize = 40;
const int unicornSize = 80;
const int CellCountWidth = 30;
const int CellCountHeight = 30;
const int offset = 4 * cellSize;
const int windowWidth = cellSize * CellCountWidth;
const int windowHeight = cellSize * CellCountHeight;

double lastUpdateTime = 0;

int minY = 10;    // 10
int maxY = 15;    // 20
int minSpan = 8;
int maxSpan = 10;
int shift = 3;

void initialVariables()
{
	minY = 10;    // 10
	maxY = 15;    // 20
	minSpan = 8;
	maxSpan = 10;
	shift = 3;
}

const int obstacleWidth = 4 * cellSize;
const int minObstaclesSpace = windowWidth - 12 * cellSize;
