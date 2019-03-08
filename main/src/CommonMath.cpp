#include "CommonMath.h"

#include <random>

std::random_device rd;
std::mt19937 gen(rd());

// detect point x and y is in two line's area 
// two line from startAngle to endAngle
// two line with x + By + C = 0
// x: point x, relative point
// y: point y, relative point
// startAngle: angle of first line
// endAngle: angle of second line
// startB: first line's coefficient B
// startC: first line's coefficient C
// endB: second line's coefficient B
// endC: second line's coefficient C
bool isInArea(int x, int y, int startAngle, int endAngle, double startB, double startC, double endB, double endC){
    //printf("x: %d\ty: %d\n", x, y);
    if(startAngle >= 0 
            && startAngle < 180 
            && endAngle > 0 
            && endAngle <= 180){
        //printf("1\n");
        if(x + y * startB + startC <= 0
                && x + y * endB + endC >= 0)
            return true;
    }
    else if(startAngle > 0 
            && startAngle <= 180
            && endAngle > 180
            && endAngle < 360){
        //printf("2\n");
        if(x + y * startB + startC <= 0
                && x + y * endB + endC <= 0)
            return true;
    }
    else if(startAngle > 180
            && startAngle < 360
            && endAngle > 180
            && endAngle <= 360){
        //printf("3\n");
        if(x + y * startB + startC >= 0
                && x + y * endB + endC <= 0)
            return true;
    }
    else if(startAngle > 180
            && startAngle <= 360
            && endAngle > 0
            && endAngle < 180){
        //printf("4\n");
        if(x + y * startB + startC >= 0 
                && x + y * endB + endC >= 0)
            return true;
    }
    return false;
}

double calculateDistance(int x1, int y1, int x2, int y2){
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

// use point x get y from linear equation x + By + C = 0
// x: point x, relative point
// B: linear equation coefficient B
// C: linear equation coefficient C
int XgetY(int x, double B, double C){
    return ((-1.0) * ((double)x + C)) / B;
}

int getRnd(int start, int end){
    std::uniform_int_distribution<int> distribution(start, end);
    return distribution(gen);
}
