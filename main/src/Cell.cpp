#include "Cell.h"

// Constructor
// gNB base class
// x: gNB x position
// y: gNB y position
// cellType: gNB CellType, Macro or Femto //FIXME maybe reduntant
Cell::Cell(int x, int y, int cellIndex, int nBeams, CellType cellType, int prachConfigIndex) : x(x), y(y), cellIndex(cellIndex), nBeams(nBeams), cellPixelSize(10), subframeIndex(0), frameIndex(0), raResponseWindow(1), cellType(cellType){
    prachConfig = new PRACHConfigFR1(prachConfigIndex);
    prachConfig->configRA();
    availiableRAO = new AvailiableRAO(nBeams, 1, 8, 64, 160, prachConfig);
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
    rars = vector<vector<RAR*>>(10);
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
    //printf("start angle: %lf\n", startAngle);
    beam = beams.at(beams.size() - 1);
    this->endB = beam->getEndB();
    this->endC = beam->getEndC();
    this->endAngle = beam->getEndAngle();
    //printf("end angle: %lf\n", endAngle);
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
        printf("UE %lu is in cell %d range\n", ue->getID(), cellIndex);
    }
    //TODO: maybe add ue to vector for storing UE(already added?)
}

bool Cell::checkUEisExist(UE *ue){
    UE *temp;
    for(unsigned int i = 0;i < ues.size();i++){
        temp = ues[i];
        if(temp->getID() == ue->getID()){
            printf("UE %lu already be added to Cell %d\n", 
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
        if(ue->receiveSI(this))
            i--;
    }
    //ue->receiveSI(this);
}

void Cell::deregisterCell(UE *ue){
    for(auto it = ues.begin();it != ues.end();it++){
        if((*it)->getID() == ue->getID()){
            printf("UE: %d removing from cell: %d\n",
                    (*it)->getID(),
                    cellIndex);
            ues.erase(it);
            break;
        }
    }
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
    availiableRAO->updateAssociationFrame();
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
}

void Cell::setSSBPerRAO(double ssbPerRAO){
    availiableRAO->setSSBPerRAO(ssbPerRAO);
    availiableRAO->updateAssociationFrame();
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
}

void Cell::setPrachConfigIndex(int prachConfigIndex){
    prachConfig->setPrachConfigIndex(prachConfigIndex);
    prachConfig->configRA();
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
}

void Cell::setRaResponseWindow(const int raResponseWindow){
    this->raResponseWindow = raResponseWindow;
}

void Cell::receivePreamble(const int raoIndex, const int preambleIndex){
    printf("receiving preamble\n");
    int respondSubframe = (subframeIndex + raResponseWindow) % 10;
    vector<RAR*>& subframeRars = rars[respondSubframe];
    RAR *rar = new RAR;
    rar->raoIndex = raoIndex;
    rar->preambleIndex = preambleIndex;
    rar->uplinkResourceIndex = subframeRars.size() + 1;
    rar->tc_rnti = subframeRars.size() + 1;
    //printf("size: %d\n", subframeRars.size());

    //printf("rao index: %d, preamble index: %d\n", 
    //        rar->raoIndex, 
    //        rar->preambleIndex);
    int insertIndex = searchRAR(subframeRars, *rar);
    //printf("insert index: %d\n", insertIndex);
    if(subframeRars.size() == insertIndex)
        subframeRars.push_back(rar);
    else if(subframeRars.size() > 0 
            && subframeRars[insertIndex]->raoIndex == rar->raoIndex 
            && subframeRars[insertIndex]->preambleIndex == rar->preambleIndex){
        printf("rao: %d, preamble: %d already exist in RAR\n",
                rar->raoIndex,
                rar->preambleIndex);
    }
    else{
        subframeRars.insert(subframeRars.begin() + insertIndex, rar);
    }
    printf("receive complete\n");
}

void Cell::transmitRAR(){
    if(!hasRAR())
        return;
    printf("Cell: %d transmitting RARs\n", cellIndex);
    vector<RAR*>& subframeRar = rars[subframeIndex];
    for(auto i = subframeRar.begin();i != subframeRar.end();i++){
        printf("%d\t%d\n", (*i)->raoIndex, (*i)->preambleIndex);
    }
    UE *ue;
    printf("rar size: %lu\n" ,subframeRar.size());
    for(decltype(ues.size()) i = 0;i < ues.size();i++){
        ue = ues.at(i);
        printf("Cell: %d transmitting RAR to UE :%d\n",
                cellIndex,
                ue->getID());
        ue->receiveRAR(subframeRar, cellIndex);
    }
    for(decltype(subframeRar.size()) i = 0;i < subframeRar.size();i++){
        delete subframeRar[i];
    }
    subframeRar.clear();
    printf("RARs transmit complete\n");
}

void Cell::receiveMsg3(Msg3& msg3){
    int insertIndex = searchMsg3(msg3s, msg3);
    if(insertIndex == msg3s.size())
        msg3s.push_back(&msg3);
    else if(msg3s.size() > 0 
            && msg3s[insertIndex]->tc_rnti == msg3.tc_rnti){
        printf("tc_rnti: %d, already exist in RAR\n",
                msg3.tc_rnti);
    }
    else{
        msg3s.insert(msg3s.begin() + insertIndex, &msg3);
    }
}

void Cell::transmitCR(){
    if(!msg3s.size())
        return;
    printf("transmitting contention resolution\n");
    UE *ue;
    for(decltype(ues.size()) i = 0;i < ues.size();i++){
        ue = ues.at(i);
        ue->receiveCR(msg3s, cellIndex);
        if(ue->isRASuccess()){
            printf("removing UE id: %lu from cell index: %d\n", 
                    ue->getID(),
                    cellIndex);
            ues.erase(ues.begin() + i);
            i--;
        }
    }
    for(decltype(msg3s.size()) i = 0;i < msg3s.size();i++){
        delete msg3s[i];
    }
    msg3s.clear();
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

int Cell::getRaResponseWindow(){
    return raResponseWindow;
}

// get cell start angle
// return: cell start angle
double Cell::getBeamStartAngle(){
    return this->beamStartAngle;
}

double Cell::getSSBPerRAO(){
    return availiableRAO->getSSBPerRAO();
}

double Cell::getCellSpanAngle(){
    return cellAngle;
}

bool Cell::hasRAR(){
    if(rars[subframeIndex].size())
        return true;
    return false;
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
