#include "UE.h"

using namespace std;

// constructor
// x: point x of ue
// y: point y of ue
// id: ue ID
UE::UE(int x, int y, unsigned long id) : UE(x, y, id, false){
}

// constructor
// x: point x of ue
// y: point y of ue
// id: ue ID
// isTest: if this class is used by testing, this value is true, 
// otherwise false
UE::UE(int x, int y, unsigned long id, bool isTest){
    setXY(x, y);
    this->id = id;
    beamIndex = -1;
    cellIndex = -1;
    beamStrength = -1;
    powerRamp = 0;
    UEPixelSize = 6;
    candidateCell = NULL;
    startRAO = 0;
    endRAO = 0;
    raStartRAO = -1;
    raEndRAO = -1;
    selectRAOIndex = -1;
    selectPreambleIndex = -1;
    uplinkResourceIndex = -1;
    tc_rnti = -1;
    preambleTransmitted = false;
    rarReceived = false;
    msg3Transmitted = false;
    raSuccess = false;
    this->isTest = isTest;
    collided = false;
    raFrame = -1;
    raSubframe = -1;
    msg3Frame = -1;
    msg3Subframe = -1;
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
        // new beam is better
        SPDLOG_TRACE("new beam is better than original one");
        this->cellIndex = cellIndex;
        this->beamIndex = beamIndex;
        this->beamStrength = beamStrength;
        return;
    }
    // old beam is better
    SPDLOG_TRACE("old beam is better\n");
}

// receive SI
// if received SI's cell is better than original cell,
// deregister the original cell and change candidate cell 
// to the received SI's cell
// if original cell is better, 
// deregister the received SI's cell since when detect UE procedure 
// will store UE context in cell
int UE::receiveSI(Cell *cell){
    if(cell->getCellIndex() == this->cellIndex){
        // TODO: set ssb-perrach-OccasionAndCBRA-preambles
        // TODO: set CRE(future work)
        SPDLOG_TRACE("UE {0} receive cell index {1}, beam index {2} system information", 
                id,
                cell->getCellIndex(),
                beamIndex);
        if(candidateCell && candidateCell->getCellIndex() != cellIndex){
            candidateCell->deregisterCell(this);
        }
        // storing cell's configuration
        this->candidateCell = cell;
        prachConfig = cell->getPRACHConfig();
        availiableRAO = cell->getAvailiableRAO();
        startRAO = beamIndex / availiableRAO->getSSBPerRAO();
        int nRAO = 1 / availiableRAO->getSSBPerRAO();
        if(nRAO > 0)
            nRAO -= 1;
        endRAO = startRAO + nRAO;
        return 0;
    }
    SPDLOG_TRACE("UE: {0} Other cell is better, doesn't need to receive cell index {1} SI", id, cell->getCellIndex());
    SPDLOG_TRACE("UE: {0} deregister from cell: {1}", 
            id,
            cell->getCellIndex());
    cell->deregisterCell(this);
    return 1;
}

// do the RA procedure
// if is testing, UE won't send preamble
void UE::doRA(){
    SPDLOG_TRACE("UE {0} doing RA", id);
    if(isTest || !preambleTransmitted){
        checkRA();
        if(raStartRAO != -1 && raEndRAO != -1){
            SPDLOG_TRACE("current subframe is for UE {0} RA", id);
            SPDLOG_TRACE("UE {0}: ra start RAO: {1}\tra end RAO: {2}", 
                    id,
                    raStartRAO,
                    raEndRAO);
            // store raos index with subframeRAOStart to subframeRAOEnd
            storeRAOsforRA(availiableRAO->getStartRAOofSubframe(),
                    availiableRAO->getEndRAOofSubframe());
            SPDLOG_TRACE("number of rao: %d\n", raos.size());
            SPDLOG_TRACE("rao index: ");
            for(unsigned int i = 0;i < raos.size();i++)
                SPDLOG_TRACE("{:4d}", raos[i]);
            if(!isTest)
                transmitMsg1();
            else
                SPDLOG_TRACE("is testing");
        }
        else
            SPDLOG_TRACE("current subframe is not for UE {0} RA", id);
    }
    else if (preambleTransmitted && rarReceived && !msg3Transmitted){
        // if preamble is transmitted and rar received
        transmitMsg3();
    }
    else if(preambleTransmitted && rarReceived && msg3Transmitted && raSuccess)
        SPDLOG_TRACE("UE {0} RA already success, wait for remove from simulation", id);
    else{
        SPDLOG_ERROR("preamble transmitted: {0}, msg3 transmitted: {1}, ra success: {2}", 
                preambleTransmitted, 
                msg3Transmitted, 
                raSuccess);
        SPDLOG_ERROR("something wrong!!!");
    }
}

// receive RAR
// rars: cell transmits rar
// cellIndex: cell index
void UE::receiveRAR(const vector<RAR*>& rars, const int cellIndex){
    SPDLOG_TRACE("rar cell index: {0}, select cell index: {1}",
            cellIndex, candidateCell->getCellIndex());
    if(cellIndex != candidateCell->getCellIndex() 
            || (!preambleTransmitted || rarReceived || msg3Transmitted))
        return;
    SPDLOG_TRACE("UE {0} receiving RAR", id);
    int index = searchRAR(rars, raos[selectRAOIndex], selectPreambleIndex);
    SPDLOG_TRACE("rar index: {0}", index);
    SPDLOG_TRACE("select rao index: {0}, searched rao index: {1}",
            raos[selectRAOIndex],
            rars[index]->raoIndex);
    SPDLOG_TRACE("select preamble index: {0}, searched preamble index: {1}",
            selectPreambleIndex,
            rars[index]->preambleIndex);
    uplinkResourceIndex = rars[index]->uplinkResourceIndex;
    tc_rnti = rars[index]->tc_rnti;
    rarReceived = true;
    msg3Frame = candidateCell->getFrameIndex();
    msg3Subframe = candidateCell->getSubframeIndex() + 1;
    if(msg3Subframe >= 10){
        msg3Frame++;
        msg3Subframe = 0;
    }
    SPDLOG_TRACE("receive complete");
}

// set active frame index and subframe index
// frameIndex: active frame index
// subframeIndex: active subframe index
void UE::setActiveTime(const int frameIndex, const int subframeIndex){
    activeFrame = frameIndex;
    activeSubframe = subframeIndex;
}

// check current timing can do RA or not
// if RA can be performed, update raStartRAO and raEndRAO
// otherwise, raStartRAO and raEndRAO is -1
void UE::checkRA(){
    SPDLOG_TRACE("checking ra availiable");
    int frameIndex = candidateCell->getFrameIndex();
    int subframeIndex = candidateCell->getSubframeIndex();
    SPDLOG_TRACE("frame: {0}, subframe: {1}", frameIndex, subframeIndex);
    raos.clear();
    if(availiableRAO->isRASubframe(frameIndex, subframeIndex)){
        SPDLOG_TRACE("UE {0}: frame index: {1}, subframe Index: {2} is for RA\n",
                id,
                frameIndex,
                subframeIndex);
        updateRAOforRA();
    }
    else{
        SPDLOG_TRACE("UE {0}: frame index: {1}, subframe index: {2} not for RA\n", 
                id,
                frameIndex,
                subframeIndex);
        raStartRAO = -1;
        raEndRAO = -1;
    }
}

// call by checkRA
// update RAOs for RA
// is current timing contain RAOs for UE to perform RA
// update raos
// this procedure will do twice if subframeStartRAO is larger than
// ue startRAO
void UE::updateRAOforRA(){
    const int subframeStartRAO = availiableRAO->getStartRAOofSubframe();
    const int subframeEndRAO = availiableRAO->getEndRAOofSubframe();
    const int totalNeedRAO = availiableRAO->getTotalNeedRAO();
    SPDLOG_TRACE("UE {0}: ssb per rao: {1}, msg1FDM: {2}, nBeams: {3}, start RAO: {4}, end RAO: {5}",
            id,
            availiableRAO->getSSBPerRAO(),
            availiableRAO->getMsg1FDM(),
            candidateCell->getnBeams(),
            startRAO,
            endRAO);
    SPDLOG_TRACE("subframe start RAO: {0}, subframe end RAO: {1}", 
            availiableRAO->getStartRAOofSubframe(),
            availiableRAO->getEndRAOofSubframe());
    updateRAOforRA(startRAO, 
            endRAO, 
            subframeStartRAO, 
            subframeEndRAO, 
            totalNeedRAO);
    //TODO: still testing
    if(raStartRAO == -1 && raEndRAO == -1){
        updateRAOforRA(startRAO + totalNeedRAO, 
                endRAO + totalNeedRAO,
                subframeStartRAO,
                subframeEndRAO,
                totalNeedRAO);
    }
}

// call by updateRAOforRA
// the second time to update
// check if subframeStartRAO is larger than ue's start RAO once time
// startRAO: start rao
// endRAO: end rao
// subframeStartRAO: subframe start rao
// subframeEndRAO: subframe end rao
// totalNeedRAO: totalNeedRAO for all ssb
// 
// will call by the condition like this
//
// |----totalNeedRAO----|----totalNeedRAO----|-----------------------------|
// startRAO--------endRAO--subframeStartRAO-------------------subframeEndRAO
void UE::updateRAOforRA(const int startRAO, const int endRAO, const int subframeStartRAO, const int subframeEndRAO, const int totalNeedRAO){
    raStartRAO = startRAO;
    raEndRAO = endRAO;
    if((subframeStartRAO <= startRAO && startRAO <= subframeEndRAO)
            || (subframeStartRAO <= endRAO && endRAO <= subframeEndRAO)){
        if(endRAO >= subframeEndRAO)
            raEndRAO = subframeEndRAO;
        if(startRAO <= subframeStartRAO)
            raStartRAO = subframeStartRAO;
    }
    else if(startRAO <= subframeStartRAO && endRAO >= subframeEndRAO){
        raStartRAO = subframeStartRAO;
        raEndRAO = subframeEndRAO;
    }
    else{
        raStartRAO = -1;
        raEndRAO = -1;
    }
}

// store raos for RA
// raStartRAO and raEndRAO only stored the range 
// raos stores the each of RAO can perform RA
// subframeStartRAO: subframe start RAO
// subframeEndRAO: subframe end RAO
void UE::storeRAOsforRA(const int subframeStartRAO, const int subframeEndRAO){
    int nRAO = 1 / availiableRAO->getSSBPerRAO();
    const int totalNeedRAO = availiableRAO->getTotalNeedRAO();
    const int totalRAOPerSubframe = availiableRAO->getTotalRAOPerSubframe();

    SPDLOG_TRACE("raStartRAO: {0}, raEndRAO: {1}", raStartRAO, raEndRAO);
    for(int i = 0;i < raEndRAO - raStartRAO + 1;i++){
        raos.push_back(raStartRAO + i);
    }
    
    // if subframe contains the number of RAOs larger than totalNeedRAO
    // means that all ssb can map to this subframe more than one time
    if(totalRAOPerSubframe > totalNeedRAO){
        while(raEndRAO + totalNeedRAO <= subframeEndRAO){
            raStartRAO += totalNeedRAO;
            raEndRAO += totalNeedRAO;
            for(int i = 0;i < raEndRAO - raStartRAO + 1;i++)
                raos.push_back(raStartRAO + i);
        }
        if(raStartRAO + totalNeedRAO <= subframeEndRAO){
            raStartRAO += totalNeedRAO;
            if(raStartRAO + nRAO < subframeEndRAO){
                raEndRAO = raStartRAO + nRAO;
            }
            else if(raStartRAO + nRAO > subframeEndRAO){
                raEndRAO = subframeEndRAO;
            }
            for(int i = 0;i < raEndRAO - raStartRAO + 1;i++)
                raos.push_back(raStartRAO + i);
        }
    }
}

// transmit msg1 aka preamble
// ue random select a preamble from availiable resource of current SSB
// and select a random RAO from availiable resource of current SSB
void UE::transmitMsg1(){
    const int startPreamble = availiableRAO->getStartNumberofPreamble(beamIndex);
    const int nPreambles = availiableRAO->getNumberofPreambles();
    raFrame = candidateCell->getFrameIndex();
    raSubframe = candidateCell->getSubframeIndex();
    raSSBPerRAO = candidateCell->getSSBPerRAO();
    raMsg1FDM = candidateCell->getMsg1FDM();
    SPDLOG_TRACE("start preambe number: {0}, number of preamble: {1}", 
            startPreamble, 
            nPreambles);
    selectRAOIndex = getRnd(0, raos.size() - 1);
    selectPreambleIndex = getRnd(startPreamble, startPreamble + nPreambles - 1);
    SPDLOG_TRACE("UE {0} select rao: {1}, select preamble: {2}", 
            id,
            raos[selectRAOIndex], 
            selectPreambleIndex);
    candidateCell->receivePreamble(raos[selectRAOIndex], 
            selectPreambleIndex);
    preambleTransmitted = true;
}

// transmit Msg3
void UE::transmitMsg3(){
    const int frame = candidateCell->getFrameIndex();
    const int subframe = candidateCell->getSubframeIndex();
    if(frame != msg3Frame || subframe != msg3Subframe){
        SPDLOG_TRACE("current frame {0} subframe {1} can not transmit msg3",
                frame,
                subframe);
        return;
    }
    Msg3 *msg3 = new Msg3;
    msg3->uplinkResourceIndex = uplinkResourceIndex;
    msg3->tc_rnti = tc_rnti;
    msg3->ueIndex = id;
    msg3->power = beamStrength + powerRamp;
    candidateCell->receiveMsg3(*msg3);
    msg3Transmitted = true;
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
unsigned long UE::getID(){
    return this->id;
}

// get ue's best beam index
// return: ue's best beam index
int UE::getBeamIndex(){
    return this->beamIndex;
}

// get ue active frame index
// return: ue active frame index
int UE::getActiveFrame(){
    return activeFrame;
}

// get ue active subframe index
// return: ue active subframe index
int UE::getActiveSubframe(){
    return activeSubframe;
}

// get ue departed frame index
// return: ue departed frame index
int UE::getDepartedFrame(){
    return departedFrame;
}

// get frame that ue perform RA
// return: ue perform RA frame
int UE::getRAFrame(){
    return raFrame;
}

// get subframe that ue perform RA
// return: ue perform RA subframe
int UE::getRASubframe(){
    return raSubframe;
}

// get msg1-FDM when ue perform RA
// return: msg1-FDM when ue perform RA
int UE::getRAMsg1FDM(){
    return raMsg1FDM;
}

// get ue selected preamble index
// return: ue selected preamble index
int UE::getSelectPreambleIndex(){
    return selectPreambleIndex;
}

// get ue selected rao index
// return: ue selected rao index
int UE::getSelectRAOIndex(){
    return raos[selectRAOIndex];
}

// get ssb-perRAO when ue perform RA
// return: ssb-perRAO when ue perform RA
double UE::getRASSBPerRAO(){
    return raSSBPerRAO;
}

// get ue departed subframe index
// return: ue departed subframe index
int UE::getDepartedSubframe(){
    return departedSubframe;
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

// receive CR
// if received CR and contained ue ID the same as itself
// RA is success
// otherwise
// RA failed, and perform RA from preamble transmission again
// CRs: CR transmitted by cell
// cellIndex: cell index
bool UE::receiveCR(const vector<Msg3*>& CRs, const int cellIndex){
    if(cellIndex != candidateCell->getCellIndex() || !msg3Transmitted)
        return false;
    int index = searchMsg3(CRs, tc_rnti);
    SPDLOG_TRACE("contention resolution index: {0}", index);
    SPDLOG_TRACE("UE TC-RNTI: {0], searched TC-RNTI: {1}",
            tc_rnti,
            CRs[index]->tc_rnti);
    SPDLOG_TRACE("UE id: {0}, searched UE id: {1}",
            id,
            CRs[index]->ueIndex);
    if(tc_rnti == CRs[index]->tc_rnti
            && id == CRs[index]->ueIndex){
        SPDLOG_TRACE("UE {0} RA success!!!", id);
        departedFrame = candidateCell->getFrameIndex();
        departedSubframe = candidateCell->getSubframeIndex();
        raSuccess = true;
    }
    else{
        SPDLOG_TRACE("UE {0} RA failed", id);
        raSuccess = false;
        preambleTransmitted = false;
        rarReceived = false;
        msg3Transmitted = false;
        collided = true;
        raFrame = -1;
        raSubframe = -1;
        msg3Frame = -1;
        msg3Subframe = -1;
        powerRamp += 5;
    }
    return true;
}

// test whether ue has binded to a cell
bool UE::isBindCell(){
    if(candidateCell)
        return true;
    return false;
}

// test whether ue has transmitted a preamble
bool UE::isPreambleTransmit(){
    return preambleTransmitted;
}

// test whether ue has received a RAR
bool UE::isRarReceived(){
    return rarReceived;
}

// test whether ue msg3 is already transmitted
bool UE::isMsg3Transmitted(){
    return msg3Transmitted;
}

// test whether ue RA already success 
bool UE::isRASuccess(){
    return raSuccess;
}

// test whether ue has been collided with other ue
bool UE::isCollided(){
    return collided;
}

// draw ue
// painter: QPainter
void UE::draw(QPainter &painter){
    if(collided)
        painter.setBrush(QBrush(QColor(200, 0, 128, 255), Qt::SolidPattern));
    else
        painter.setBrush(QBrush(QColor(200, 128, 255, 255), Qt::SolidPattern));
    painter.drawEllipse(x - UEPixelSize / 2, 
            y - UEPixelSize / 2,
            UEPixelSize,
            UEPixelSize);
}

// get stored RAOs
// typicallly testing use this method
// other cell may NOT using this method
vector<int>& UE::getRAOs(){
    return raos;
}

// destructor
UE::~UE(){
    SPDLOG_TRACE("ue deleted");
}
