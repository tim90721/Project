#include "Cell.h"

// Constructor
// gNB base class
// x: gNB x position
// y: gNB y position
// cellType: gNB CellType, Macro or Femto //FIXME maybe reduntant
Cell::Cell(int x, int y, int cellIndex, int nBeams, celltype::CellType cellType, int prachConfigIndex, int nPreambles, int cellBW, int ssbSCS, double preambleSCS) : x(x), y(y), cellIndex(cellIndex), nBeams(nBeams), cellPixelSize(10), subframeIndex(0), frameIndex(0), raResponseWindow(1), nPreambles(nPreambles), cellBW(cellBW), ssbSCS(ssbSCS), preambleSCS(preambleSCS), cellType(cellType){
    double ssbperRAO = 1;
    int msg1FDM = 1;
    //int nPreambles = 64;
    SPDLOG_TRACE("cell {0} nPreambles: {1}", this->cellIndex, this->nPreambles);
    SPDLOG_INFO("cell {0} cell BW: {1}", this->cellIndex, this->cellBW);
    SPDLOG_INFO("cell{0} preamble SCS: {1}", this->cellIndex, this->preambleSCS);
    estimateUEs = 0;
    prachConfig = new PRACHConfigFR1(prachConfigIndex);
    prachConfig->configRA();
    availiableRAO = new AvailiableRAO(nBeams, ssbperRAO, msg1FDM, nPreambles, 160, prachConfig);
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
    rars = vector<vector<RAR*>>(10);
    mRA = new MonitorRAFunction(availiableRAO, prachConfig);
    successUEs = 0;
    failedUEs = 0;
    startBeamIndex = -1;
    endBeamIndex = -1;
    updateSSBStartAndEndIndex();
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
    SPDLOG_TRACE("cell {0} startAngle: {1}, spanAngle: {2}",
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
        SPDLOG_TRACE("UE {0} is in cell {1} range", ue->getID(), cellIndex);
    }
}

// check ue is in this cell
// ue: the UE need to be checked 
bool Cell::checkUEisExist(UE *ue){
    UE *temp;
    for(unsigned int i = 0;i < ues.size();i++){
        temp = ues[i];
        if(temp->getID() == ue->getID()){
            SPDLOG_TRACE("UE {0} already be added to Cell {1}", 
                    temp->getID(),
                    cellIndex);
            return true;
        }
    }
    return false;
}

// check beam index in current subframe, frame is allowed to 
// transmit braodcast message
// beamIndex: beam index
// return: true for allowed
bool Cell::isBeamAllowedPBCH(const int beamIndex){
    SPDLOG_TRACE("start beam index: {0}", startBeamIndex);
    SPDLOG_TRACE("end beam index: {0}", endBeamIndex);
    SPDLOG_TRACE("beam index: {0}", beamIndex);
    if(startBeamIndex == -1 && endBeamIndex == -1){
        SPDLOG_TRACE("current frame {0} subframe {1} is not for PBCH", 
                frameIndex, subframeIndex);
        return false;
    }
    else if(startBeamIndex <= beamIndex && beamIndex < endBeamIndex){
        return true;
    }
    SPDLOG_TRACE("current frame {0} subframe {1} is not for beam {2} PBCH", 
            frameIndex, subframeIndex, beamIndex);
    return false;
}

// update start and end ssb index that is allowed to transmit PBCH
void Cell::updateSSBStartAndEndIndex(){
    if(frameIndex % 2 == 1 || (frameIndex % 2 == 0 && subframeIndex > 4)){
        SPDLOG_TRACE("next frame {0} subframe {1} is not for PBCH", 
                frameIndex, subframeIndex);
        startBeamIndex = -1;
        endBeamIndex = -1;
    }
    switch(ssbSCS){
        case 15:
            startBeamIndex = subframeIndex * 2;
            endBeamIndex = (subframeIndex + 1) * 2;
            if(((nBeams == 4) && (subframeIndex > 1))
                    || subframeIndex > 3){
                startBeamIndex = -1;
                endBeamIndex = -1;
            }
            break;
        case 30:
            startBeamIndex = subframeIndex * 4;
            endBeamIndex = (subframeIndex + 1) * 4;
            if((nBeams == 4 && subframeIndex > 0)
                    || subframeIndex > 1){
                startBeamIndex = -1;
                endBeamIndex = -1;
            }
            break;
        case 120:
            startBeamIndex = subframeIndex * 16;
            endBeamIndex = (subframeIndex + 1) * 16;
            if(subframeIndex > 1){
                endBeamIndex -= 4;
            }
            if(subframeIndex > 2){
                startBeamIndex -= 4;
            }
            if(subframeIndex == 4){
                startBeamIndex = 56;
                endBeamIndex = 63;
            }
            break;
        case 240:
            startBeamIndex = subframeIndex * 32;
            endBeamIndex = (subframeIndex + 1) * 32;
            if(subframeIndex > 1){
                startBeamIndex = -1;
                endBeamIndex = -1;
            }
            break;
        default:
            SPDLOG_WARN("ssb SCS not support now");
            startBeamIndex = -1;
            endBeamIndex = -1;
    }
}

// broadcasting cell's SI
void Cell::broadcastSI(){
    SPDLOG_TRACE("Broadcast cell index {0} system information", cellIndex);
    UE *ue;
    for(unsigned int i = 0;i < ues.size();i++){
        ue = ues.at(i);
        if(isBeamAllowedPBCH(ue->getBeamIndex()) && ue->receiveSI(this)){
                i--;
        }
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
            SPDLOG_TRACE("UE: {0} removing from cell: {1}",
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
    if((frameIndex * 10 + subframeIndex) % 160 == 0 && !TESTING){
        SPDLOG_INFO("next subframe can modify rao configuration");
        SPDLOG_TRACE("next frame: {0}, next subframe: {1}", 
                frameIndex,
                subframeIndex);
        successUEs = mRA->getSuccessUEs();
        failedUEs = mRA->getFailedUEs();
        mRA->updateRAOs();
        estimateUEs = mRA->getEstimateUEs();
    } 
    availiableRAO->updateStartandEndRAOofSubframe(frameIndex, subframeIndex);
    updateSSBStartAndEndIndex();
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
    SPDLOG_TRACE("cell {0} receiving preamble", cellIndex);
    int respondSubframe = (subframeIndex + raResponseWindow) % 10;
    vector<RAR*>& subframeRars = rars[respondSubframe];
    RAR *rar = new RAR;
    rar->raoIndex = raoIndex;
    rar->preambleIndex = preambleIndex;
    rar->uplinkResourceIndex = subframeRars.size() + 1;
    rar->tc_rnti = subframeRars.size() + 1;
    SPDLOG_TRACE("size: {0}", subframeRars.size());

    SPDLOG_TRACE("rao index: {0}, preamble index: {1}", 
            rar->raoIndex, 
            rar->preambleIndex);
    int insertIndex = searchRAR(subframeRars, *rar);
    SPDLOG_TRACE("insert index: {0}", insertIndex);
    
    // if searched index is the end of stored rar
    // push rar directly in end of subframeRars
    if(subframeRars.size() == insertIndex)
        subframeRars.push_back(rar);
    else if(subframeRars.size() > 0 
            && subframeRars[insertIndex]->raoIndex == rar->raoIndex 
            && subframeRars[insertIndex]->preambleIndex == rar->preambleIndex){
        // the corresponding rar is already exist in stored Rars
        SPDLOG_TRACE("rao: {0}, preamble: {1} already exist in RAR",
                rar->raoIndex,
                rar->preambleIndex);
        delete rar;
    }
    else{
        // otherwise, store the new RAR in searched index 
        subframeRars.insert(subframeRars.begin() + insertIndex, rar);
    }
    SPDLOG_TRACE("cell {0} receive complete", cellIndex);
}

// transmit RAR if cell has RAR stored
void Cell::transmitRAR(){
    if(!hasRAR())
        return;
    SPDLOG_TRACE("Cell: {0} transmitting RARs", cellIndex);
    vector<RAR*>& subframeRar = rars[subframeIndex];
    for(auto i = subframeRar.begin();i != subframeRar.end();i++){
        SPDLOG_TRACE("rao: {0}\tpreamble: {1}", (*i)->raoIndex, (*i)->preambleIndex);
    }
    UE *ue;
    SPDLOG_TRACE("rar size: {0}" ,subframeRar.size());
    for(decltype(ues.size()) i = 0;i < ues.size();i++){
        ue = ues.at(i);
        if(ue->isBindCell()){
            SPDLOG_TRACE("Cell: {0} transmitting RAR to UE :{1}",
                    cellIndex,
                    ue->getID());
            ue->receiveRAR(subframeRar, cellIndex);
        }
    }

    // delete each stored and transmitted RAR
    for(decltype(subframeRar.size()) i = 0;i < subframeRar.size();i++){
        delete subframeRar[i];
    }
    subframeRar.clear();
    SPDLOG_TRACE("RARs transmit complete");
}

// receive Msg3 transmitted by UE
// msg3: msg3 forged and transmitted by UE
void Cell::receiveMsg3(Msg3& msg3){
    int insertIndex = searchMsg3(msg3s, msg3);
    if(insertIndex == msg3s.size())
        msg3s.push_back(&msg3);
    else if(msg3s.size() > 0 
            && msg3s[insertIndex]->tc_rnti == msg3.tc_rnti){
        SPDLOG_TRACE("tc_rnti: {0}, already exist in RAR",
                msg3.tc_rnti);
        if(msg3s[insertIndex]->power < msg3.power){
            SPDLOG_TRACE("new msg3 power is bigger than older one");
            SPDLOG_TRACE("old msg3 ue index: {0}", msg3s[insertIndex]->ueIndex);
            SPDLOG_TRACE("old msg3 power: {0}", msg3s[insertIndex]->power);
            SPDLOG_TRACE("new msg3 ue index: {0}", msg3.ueIndex);
            SPDLOG_TRACE("new msg3 power: {0}", msg3.power);
            msg3s[insertIndex]->ueIndex = msg3.ueIndex;
            msg3s[insertIndex]->power = msg3.power;
        }
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
    SPDLOG_TRACE("transmitting contention resolution");
    UE *ue;
    int countSuccess = 0;
    int countFailed = 0;
    for(decltype(ues.size()) i = 0;i < ues.size();i++){
        ue = ues.at(i);
        if(ue->isBindCell() && ue->receiveCR(msg3s, cellIndex)){
            if(ue->isRASuccess()){
                SPDLOG_TRACE("removing UE id: {0} from cell index: {1}", 
                        ue->getID(),
                        cellIndex);
                ues.erase(ues.begin() + i);
                i--;
                countSuccess++;
            }
            else{
                countFailed++;
            }
        }
    }

    mRA->recordUEsCondition(countSuccess, countFailed);

    // delete the stored msg3
    for(decltype(msg3s.size()) i = 0;i < msg3s.size();i++){
        delete msg3s[i];
    }
    msg3s.clear();
}

// restore monitor ra function to initial condition
void Cell::restoreMonitorRA2Initial(){
    mRA->restore2Initial();
    successUEs = 0;
    failedUEs = 0;
    estimateUEs = 0;
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

// get ra-ResponseWindow
// return: ra-ResponseWindow
int Cell::getRaResponseWindow(){
    return raResponseWindow;
}

// get prach-ConfigurationIndex
// return: prach-ConfigurationIndex
int Cell::getPrachConfigIndex(){
    return prachConfig->getPrachConfigIndex();
}

// get RA attempt period
// return: tau
int Cell::getTau(){
    return mRA->getTau();
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

// get cell preamble SCS
// return cell's preamble SCS
double Cell::getPreambleSCS(){
    return preambleSCS;
}

// get current channel capacity
// return: current channel capacity
double Cell::getTotalChannelCapacity(){
    return mRA->getTotalDelta();
}

// get success ues count record from monitor ra function
// return: success ues count
unsigned long Cell::getSuccessUEs(){
    if(ues.size() == 0 && (frameIndex * 10 + subframeIndex) % 16 != 0)
        return mRA->getSuccessUEs();
    return successUEs;
}

// get failed ues count record from monitor ra function
// return: failed ues count
unsigned long Cell::getFailedUEs(){
    if(ues.size() == 0 && (frameIndex * 10 + subframeIndex) % 16 != 0)
        return mRA->getFailedUEs();
    return failedUEs;
}

// get estimate ues from monitor ra function
// return: estimate ues count
double Cell::getEstimateUEs(){
    return estimateUEs;
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

// destructor
Cell::~Cell(){
    SPDLOG_TRACE("cell destructor");
    delete mRA;
    delete prachConfig;
    delete availiableRAO;
}
