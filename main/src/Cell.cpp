#include "Cell.h"

// Constructor
// gNB base class
// x: gNB x position
// y: gNB y position
// cellType: gNB CellType, Macro or Femto //FIXME maybe reduntant
Cell::Cell(int x, int y, int cellIndex, int nBeams, celltype::CellType cellType, int prachConfigIndex) : x(x), y(y), cellIndex(cellIndex), nBeams(nBeams), cellPixelSize(10), subframeIndex(0), frameIndex(0), raResponseWindow(1), cellType(cellType){
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

// detect ue is this cell's area
// if ue is in this cell, add this ue to this cell's ue vector
// ue: the ue to be detected
void Cell::detectUE(UE *ue){
    //printf("start:%d\tend:%d\n", this->startAngle, this->endAngle);
    // detect ue is in cell span angle area
    if(checkUEisExist(ue))
        return;
    double distance = calculateDistance(ue->getX(), ue->getY(),
            getX(), getY());
    printf("cell %d startAngle: %f, spanAngle: %f\n",
            cellIndex,
            startAngle,
            cellAngle);
    if(isInArea(ue->getX(), ue->getY(),
                getX(), getY(),
                startAngle,
                cellAngle,
                cellSupportDistance / 2)){
        Beam *beam;
        for(unsigned int i = 0;i < beams.size();i++){
            beam = beams.at(i);
            beam->detectUE(ue, 
                    ((double)(this->cellSupportDistance / 2)) - distance);
        }
        ues.push_back(ue);
        printf("UE %lu is in cell %d range\n", ue->getID(), cellIndex);
    }
}

// check ue is in this cell
// ue: the UE need to be checked 
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

// broadcasting cell's SI
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

// deregister a ue
// if a ue have another cell better than this one
// ue call this function for removing itself from this cell
// since when cell detect a ue is in this cell, 
// cell will add the UE automatically
// as a result, in order to prevent ue receving other cell's 
// RAR or CR which may cause error
// ue need to deregister the cell which it should not listen
// ue: the UE need to be deregisted
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

// update the subframe
// if subframe is add to 10
// mod subframe by 10 and add frame index
// also, update availiableRAO's start and end RAO of subframe
void Cell::updateSubframe(){
    ++subframeIndex;
    if(subframeIndex == 10){
        frameIndex++;
        subframeIndex %= 10;
    }
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
}

// reset the subframe and frame nubmer
void Cell::resetFrame(){
    this->frameIndex = 0;
    this->subframeIndex = 0;
}

// set msg1-fdm and update association frame and 
// start and end RAO of subframe
// msg1FDM: the parameter msg1-FDM in TS 38.331
void Cell::setMsg1FDM(int msg1FDM){
    availiableRAO->setMsg1FDM(msg1FDM);
    availiableRAO->updateAssociationFrame();
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
}

// set ssb-perRAO and update association frame and 
// start and end RAO of subframe
// ssbPerRAO: corresponding to TS 38.331 ssb-perRACH-Occasion
void Cell::setSSBPerRAO(double ssbPerRAO){
    availiableRAO->setSSBPerRAO(ssbPerRAO);
    availiableRAO->updateAssociationFrame();
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
}

// set prach-ConfigurationIndex and update RA parameters and
// update start and end RAO of subframe
// prachConfigIndex: corresponding to TS 38.331 prach-ConfigurationIndex
void Cell::setPrachConfigIndex(int prachConfigIndex){
    prachConfig->setPrachConfigIndex(prachConfigIndex);
    prachConfig->configRA();
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
}

// set raResponseWindow
// raResponseWindow: corresponding to TS 38.331 ra-ResponseWindow
void Cell::setRaResponseWindow(const int raResponseWindow){
    this->raResponseWindow = raResponseWindow;
}

// receive preamble
// ue will send preamble in a rao
// if cell receive a preamble, it store the preamble index and 
// rao index in (subframe index + rareponsewindow)'s rar 
// waiting to send in (subframe index + rareponsewindow)
// the RARs will store in ascending order firsy by rao index then
// preamble index
// raoIndex: ue send ra preamble's rao index
// preambleIndex: ue send preamble index 
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
    
    // if searched index is the end of stored rar
    // push rar directly in end of subframeRars
    if(subframeRars.size() == insertIndex)
        subframeRars.push_back(rar);
    else if(subframeRars.size() > 0 
            && subframeRars[insertIndex]->raoIndex == rar->raoIndex 
            && subframeRars[insertIndex]->preambleIndex == rar->preambleIndex){
        // the corresponding rar is already exist in stored Rars
        printf("rao: %d, preamble: %d already exist in RAR\n",
                rar->raoIndex,
                rar->preambleIndex);
        delete rar;
    }
    else{
        // otherwise, store the new RAR in searched index 
        subframeRars.insert(subframeRars.begin() + insertIndex, rar);
    }
    printf("receive complete\n");
}

// transmit RAR if cell has RAR stored
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

    // delete each stored and transmitted RAR
    for(decltype(subframeRar.size()) i = 0;i < subframeRar.size();i++){
        delete subframeRar[i];
    }
    subframeRar.clear();
    printf("RARs transmit complete\n");
}

// receive Msg3 transmitted by UE
// msg3: msg3 forged and transmitted by UE
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

// transmit CR if has stored CR
// CR is alternatively the Msg3 transmitted by UE
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

    // delete the stored msg3
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
void Cell::setCellType(celltype::CellType cellType){
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

// get subframe index
// return: subframe index
int Cell::getSubframeIndex(){
    return this->subframeIndex;
}

// get frame index
// return: frame index
int Cell::getFrameIndex(){
    return this->frameIndex;
}

// get msg1-FDM
// return: msg1-FDM
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

// get SSBPerRAO
// return: ssb-perRACH-Occasion
double Cell::getSSBPerRAO(){
    return availiableRAO->getSSBPerRAO();
}

// get cell cover angle
// return: cell cover angle
double Cell::getCellSpanAngle(){
    return cellAngle;
}

// is this cell has stored RAR
// return: true if has stored RAR, otherwise is false
bool Cell::hasRAR(){
    if(rars[subframeIndex].size())
        return true;
    return false;
}

// Get gNB celltype
celltype::CellType Cell::getCellType(){
    return this->cellType;
}

// get IPRACHConfig, typically used by UE
// kind of SI
// return: IPRACHConfig
IPRACHConfig* Cell::getPRACHConfig(){
    return prachConfig;
}

// get IAvailiableRAO, typically used by UE
// kind of SI
// return: IAvailiableRAO
IAvailiableRAO* Cell::getAvailiableRAO(){
    return availiableRAO;
}
