#ifndef COMMON_MATH
#define COMMON_MATH
#include <math.h>
#include <stdio.h>

bool isInArea(int x, int y, int startAngle, int endAngle, double startB, double startC, double endB, double endC);
bool isInArea(const int x1, const int y1, const int x2, const int y2, const double startAngle, const double endAngle, const double distance);
double calculateDistance(int x1, int y1, int x2, int y2);
int XgetY(int x, double B, double C);
int getRnd(int start, int end);
#endif
