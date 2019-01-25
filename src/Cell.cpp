#include "Cell.h"

// Constructor
// gNB base class
// x: gNB x position
// y: gNB y position
// cellType: gNB CellType, Macro or Femto //FIXME maybe reduntant
Cell::Cell(int x, int y, CellType cellType){
    this->x = x;
    this->y = y;
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

// Set gNB cell support distance(associate with cell size)
void Cell::setCellSupportDistance(int supportDistance){
    this->cellSupportDistance = supportDistance;
}

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

// Get gNB celltype
CellType Cell::getCellType(){
    return this->cellType;
}
