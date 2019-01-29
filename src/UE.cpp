#include "UE.h"

UE::UE(int x, int y){
    setXY(x, y);
    this->beamIndex = -1;
    this->cellIndex = -1;
    this->beamStrength = -1;
    this->UEPixelSize = 6;
}

void UE::setXY(int x, int y){
    this->x = x;
    this->y = y;
}

int UE::getX(){
    return this->x;
}

int UE::getY(){
    return this->y;
}

int UE::getBeamIndex(){
    return this->beamIndex;
}

int UE::getCellIndex(){
    return this->cellIndex;
}

int UE::getBeamStrength(){
    return this->beamStrength;
}

void UE::drawUE(QPainter &painter){
    painter.drawEllipse(x - UEPixelSize / 2, 
            y - UEPixelSize / 2,
            UEPixelSize,
            UEPixelSize);
}

