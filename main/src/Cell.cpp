#include "Cell.h"

// Constructor
// gNB base class
// x: gNB x position
// y: gNB y position
// cellType: gNB CellType, Macro or Femto //FIXME maybe reduntant
Cell::Cell(int x, int y, int cellIndex, int nBeams, CellType cellType, int prachConfigIndex) : x(x), y(y), cellIndex(cellIndex), nBeams(nBeams), cellPixelSize(10), subframeIndex(0), frameIndex(0), cellType(cellType){
    prachConfig = new PRACHConfigFR1(prachConfigIndex);
    prachConfig->configRA();
    availiableRAO = new AvailiableRAO(nBeams, 1 , 1, 64, 160, prachConfig);
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
    
}

// Set gNB x position
void Cell::setX(int x){
    this->x = x;
}

// Set gNB y position
void Cell::setY(int y){
    this->y = y;
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
    //printf("%f\n", beamStartAngle);
}

// set cell index
// cellIndex: cell index
void Cell::setCellIndex(int cellIndex){
    this->cellIndex = cellIndex;
}

// find cell cover area equation
void Cell::findCellCoverAreaEquation(){
    Beam *beam;
    for(unsigned int i = 0;i < beams.size();i++){
        beam = beams.at(i);
        beam->findBeamCoverAreaEquation();
    }
    beam = beams.at(0);
    this->startB = beam->getStartB();
    this->startC = beam->getStartC();
    this->startAngle = beam->getStartAngle();
    beam = beams.at(beams.size() - 1);
    this->endB = beam->getEndB();
    this->endC = beam->getEndC();
    this->endAngle = beam->getEndAngle();
}

// detect ue is this cell's area
// if ue is in this cell, add this ue to this cell's ue vector
// ue: the ue to be detected
void Cell::detectUE(UE *ue){
    //printf("start:%d\tend:%d\n", this->startAngle, this->endAngle);
    // detect ue is in cell span angle area
    if(checkUEisExist(ue))
        return;
    double distance = calculateDistance(ue->getX(),
            ue->getY(),
            this->x,
            this->y);
    if(distance <= (this->cellSupportDistance / 2)
            && isInArea(ue->getX() - this->x, 
                this->y - ue->getY(),
                this->startAngle,
                this->endAngle,
                this->startB,
                this->startC,
                this->endB,
                this->endC)){
        Beam *beam;
        for(unsigned int i = 0;i < beams.size();i++){
            beam = beams.at(i);
            beam->detectUE(ue, 
                    ((double)(this->cellSupportDistance / 2)) - distance);
        }
        ues.push_back(ue);
        printf("UE %d is in cell %d range\n", ue->getID(), cellIndex);
    }
    //TODO: maybe add ue to vector for storing UE(already added?)
}

bool Cell::checkUEisExist(UE *ue){
    UE *temp;
    for(unsigned int i = 0;i < ues.size();i++){
        temp = ues[i];
        if(temp->getID() == ue->getID()){
            printf("UE %d already be added to Cell %d\n", 
                    temp->getID(),
                    cellIndex);
            return true;
        }
    }
    return false;
}

void Cell::broadcastSI(){
    printf("Broadcast cell index %d system information\n", this->cellIndex);
    UE *ue;
    for(unsigned int i = 0;i < ues.size();i++){
        ue = ues.at(i);
        ue->receiveSI(this);
    }
    //ue->receiveSI(this);
}

void Cell::updateSubframe(){
    ++subframeIndex;
    if(subframeIndex == 10){
        frameIndex++;
        subframeIndex %= 10;
    }
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
}

void Cell::resetFrame(){
    this->frameIndex = 0;
    this->subframeIndex = 0;
}

void Cell::setMsg1FDM(int msg1FDM){
    availiableRAO->setMsg1FDM(msg1FDM);
}

void Cell::setSSBPerRAO(double ssbPerRAO){
    availiableRAO->setSSBPerRAO(ssbPerRAO);
}

void Cell::setPrachConfigIndex(int prachConfigIndex){
    prachConfig->setPrachConfigIndex(prachConfigIndex);
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

// get cell index
// return: cell index
int Cell::getCellIndex(){
    return this->cellIndex;
}

int Cell::getSubframeIndex(){
    return this->subframeIndex;
}

int Cell::getFrameIndex(){
    return this->frameIndex;
}

int Cell::getMsg1FDM(){
    return availiableRAO->getMsg1FDM();
}

// get cell start angle
// return: cell start angle
double Cell::getBeamStartAngle(){
    return this->beamStartAngle;
}

double Cell::getSSBPerRAO(){
    return availiableRAO->getSSBPerRAO();
}

// Get gNB celltype
CellType Cell::getCellType(){
    return this->cellType;
}

IPRACHConfig* Cell::getPRACHConfig(){
    return prachConfig;
}

IAvailiableRAO* Cell::getAvailiableRAO(){
    return availiableRAO;
}
