#include "CommonMath.h"

bool isInArea(int x, int y, int startAngle, int endAngle, double startB, double startC, double endB, double endC){
    if(startAngle > 0 
            && startAngle < 180 
            && endAngle > 0 
            && endAngle <= 180){
        if(x + y * startB + startC <= 0
                && x + y * endB + endC >= 0)
            return true;
    }
    else if(startAngle > 0 
            && startAngle <= 180
            && endAngle > 180
            && endAngle < 360){
        if(x + y * startB + startC <= 0
                && x + y * endB + endC <= 0)
            return true;
    }
    else if(startAngle > 180
            && startAngle < 360
            && endAngle > 180
            && endAngle <= 360){
        if(x + y * startB + startC >= 0
                && x + y * endB + endC <= 0)
            return true;
    }
    else if(startAngle > 180
            && startAngle <= 360
            && endAngle > 0
            && endAngle < 180){
        if(x + y * startB + startC >= 0 
                && x + y * endB + endC >= 0)
            return true;
    }
    return false;
}
