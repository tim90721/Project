#ifndef COMMON_MATH
#define COMMON_MATH
#include <math.h>
#include <stdio.h>

bool isInArea(int x, int y, int startAngle, int endAngle, double startB, double startC, double endB, double endC);
bool isInRange(int x1, int y1, int x2, int y2, int range);
int XgetY(int x, double B, double C);
#endif
