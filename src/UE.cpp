#include "UE.h"

// constructor
// x: point x of ue
// y: point y of ue
UE::UE(int x, int y, int id){
    setXY(x, y);
    this->id = id;
    this->beamIndex = -1;
    this->cellIndex = -1;
    this->beamStrength = -1;
    this->UEPixelSize = 6;
}

// set ue's point x and y
// x: point x of ue
// y: point y of ue
void UE::setXY(int x, int y){
    this->x = x;
    this->y = y;
}

// set cell index, beam index, beam strength
// if new beam strength is higher than old beam strength
// update information to new beam
// cellIndex: cell index related to the beam
// beamIndex: beam index
// beamstrength: beam strength, power
void UE::setBeam(int cellIndex, int beamIndex, int beamStrength){
    if(beamStrength > this->beamStrength){
        //printf("new beam is better than original one\n");
        this->cellIndex = cellIndex;
        this->beamIndex = beamIndex;
        this->beamStrength = beamStrength;
        return;
    }
    //printf("old beam is better\n");
}

// get ue's point x
// return: point x of ue
int UE::getX(){
    return this->x;
}

// get ue's point y
// return: point y of ue
int UE::getY(){
    return this->y;
}

// get ue's id
// return: ue's id
int UE::getID(){
    return this->id;
}

// get ue's best beam index
// return: ue's best beam index
int UE::getBeamIndex(){
    return this->beamIndex;
}

// get ue's best cell index
// return: ue's best cell index
int UE::getCellIndex(){
    return this->cellIndex;
}

// get beam strength
// return: best beam's strength
int UE::getBeamStrength(){
    return this->beamStrength;
}

// draw ue
// painter: QPainter
void UE::drawUE(QPainter &painter){
    painter.drawEllipse(x - UEPixelSize / 2, 
            y - UEPixelSize / 2,
            UEPixelSize,
            UEPixelSize);
}

