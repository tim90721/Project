#include "Cell.h"

// Constructor
// gNB base class
// x: gNB x position
// y: gNB y position
// cellType: gNB CellType, Macro or Femto //FIXME maybe reduntant
Cell::Cell(int x, int y, int cellIndex, int nBeams, CellType cellType){
    this->x = x;
    this->y = y;
    this->cellIndex = cellIndex;
    setnBeams(nBeams);
    this->cellType = cellType;
}

// Set gNB x position
void Cell::setX(int x){
    this->x = x;
    Beam *beam;
    for(int i = 0;i < (int)beams.size();i++){
        beam = beams.at(i);
        beam->setX(x);
    }
}

// Set gNB y position
void Cell::setY(int y){
    this->y = y;
    Beam *beam;
    for(int i = 0;i < (int)beams.size();i++){
        beam = beams.at(i);
        beam->setY(y);
    }
}

// set gNB number of support beams
// nBeams: number of support beams
void Cell::setnBeams(int nBeams){
    this->nBeams = nBeams;
}

// Set gNB cell support distance(associate with cell size)
void Cell::setCellSupportDistance(int supportDistance){
    this->cellSupportDistance = supportDistance;
}

// calculate beam start angle based on first mouse click coordinate and
// second mouse click coordinate
// diffX: the difference of x1 and x2
// diffY: the difference of y1 and y2
void Cell::setBeamStartAngle(int diffX, int diffY){
    beamStartAngle = atan2(diffY, diffX) * 180 / M_PI;
}

// set cell index
// cellIndex: cell index
void Cell::setCellIndex(int cellIndex){
    this->cellIndex = cellIndex;
}

// get cell support distance
int Cell::getCellSupportDistance(){
    return this->cellSupportDistance;
}

// Set gNB cellType
void Cell::setCellType(CellType cellType){
    this->cellType = cellType;
}

// Get gNB x position
int Cell::getX(){
    return this->x;
}

// Get gNB y position
int Cell::getY(){
    return this->y;
}

// get gNB number of support beams
// return number of support beams
int Cell::getnBeams(){
    return this->nBeams;
}

// get cell start angle
// return: cell start angle
double Cell::getBeamStartAngle(){
    return this->beamStartAngle;
}

// get cell index
// return: cell index
int Cell::getCellIndex(){
    return this->cellIndex;
}

// Get gNB celltype
CellType Cell::getCellType(){
    return this->cellType;
}
