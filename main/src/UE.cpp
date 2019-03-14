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
    this->beamIndex = -1;
    this->cellIndex = -1;
    this->beamStrength = -1;
    this->UEPixelSize = 6;
    this->candidateCell = NULL;
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
        //printf("new beam is better than original one\n");
        this->cellIndex = cellIndex;
        this->beamIndex = beamIndex;
        this->beamStrength = beamStrength;
        return;
    }
    // old beam is better
    //printf("old beam is better\n");
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
        printf("UE %lu receive cell index %d, beam index %d system information\n", 
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
    printf("UE: %lu Other cell is better, doesn't need to receive cell index %d SI\n", id, cell->getCellIndex());
    printf("UE: %lu deregister from cell :%d\n", 
            id,
            cell->getCellIndex());
    cell->deregisterCell(this);
    return 1;
}

// do the RA procedure
// if is testing, UE won't send preamble
void UE::doRA(){
    printf("UE %lu doing RA\n", id);
    if(isTest || !preambleTransmitted){
        checkRA();
        if(raStartRAO != -1 && raEndRAO != -1){
            printf("current subframe is for UE %lu RA\n", id);
            printf("UE %lu: ra start RAO: %d\tra end RAO: %d\n", 
                    id,
                    raStartRAO,
                    raEndRAO);
            // store raos index with subframeRAOStart to subframeRAOEnd
            storeRAOsforRA(availiableRAO->getStartRAOofSubframe(),
                    availiableRAO->getEndRAOofSubframe());
            printf("number of rao: %d\n", raos.size());
            printf("rao index: ");
            for(unsigned int i = 0;i < raos.size();i++)
                printf("%4d", raos[i]);
            printf("\n");
            if(!isTest)
                transmitMsg1();
            else
                printf("testing\n");
        }
        else{
            printf("current subframe is not for UE %lu RA\n", id);
        }
    }
    else if (preambleTransmitted && rarReceived && !msg3Transmitted){
        // if preamble is transmitted and rar received
        transmitMsg3();
    }
    else if(preambleTransmitted && rarReceived && msg3Transmitted && raSuccess){
        printf("RA already success, wait for remove from simulation\n");
    }
    else{
        printf("%d, %d, %d\n", preambleTransmitted, msg3Transmitted, raSuccess);
        printf("something wrong!!!\n");
    }
}

// receive RAR
// rars: cell transmits rar
// cellIndex: cell index
void UE::receiveRAR(const vector<RAR*>& rars, const int cellIndex){
    printf("rar cell index: %d, select cell index: %d\n",
            cellIndex, candidateCell->getCellIndex());
    if(cellIndex != candidateCell->getCellIndex() 
            || (!preambleTransmitted || msg3Transmitted))
        return;
    printf("UE %lu receiving RAR\n", id);
    int index = searchRAR(rars, raos[selectRAOIndex], selectPreambleIndex);
    printf("rar index: %d\n", index);
    printf("select rao index: %d, searched rao index: %d\n",
            raos[selectRAOIndex],
            rars[index]->raoIndex);
    printf("select preamble index: %d, searched preamble index: %d\n",
            selectPreambleIndex,
            rars[index]->preambleIndex);
    uplinkResourceIndex = rars[index]->uplinkResourceIndex;
    tc_rnti = rars[index]->tc_rnti;
    rarReceived = true;
    printf("receive complete\n");
}

// receive CR
// if received CR and contained ue ID the same as itself
// RA is success
// otherwise
// RA failed, and perform RA from preamble transmission again
// CRs: CR transmitted by cell
// cellIndex: cell index
void UE::receiveCR(const vector<Msg3*>& CRs, const int cellIndex){
    if(cellIndex != candidateCell->getCellIndex() || !msg3Transmitted)
        return;
    int index = searchMsg3(CRs, tc_rnti);
    printf("contention resolution index: %d\n", index);
    printf("UE TC-RNTI: %d, searched TC-RNTI: %d\n",
            tc_rnti,
            CRs[index]->tc_rnti);
    printf("UE id: %lu, searched UE id: %lu\n",
            id,
            CRs[index]->ueIndex);
    if(tc_rnti == CRs[index]->tc_rnti
            && id == CRs[index]->ueIndex){
        printf("RA success!!!\n");
        raSuccess = true;
    }
    else{
        printf("RA failed\n");
        raSuccess = false;
        preambleTransmitted = false;
        rarReceived = false;
        msg3Transmitted = false;
        collided = true;
    }
}

// check current timing can do RA or not
// if RA can be performed, update raStartRAO and raEndRAO
// otherwise, raStartRAO and raEndRAO is -1
void UE::checkRA(){
    printf("checking ra availiable\n");
    int frameIndex = candidateCell->getFrameIndex();
    int subframeIndex = candidateCell->getSubframeIndex();
    printf("frame: %d, subframe: %d\n", frameIndex, subframeIndex);
    raos.clear();
    if(availiableRAO->isRASubframe(frameIndex, subframeIndex)){
        printf("UE %lu: frame index: %d, subframe Index: %d is for RA\n",
                id,
                frameIndex,
                subframeIndex);
        updateRAOforRA();
    }
    else{
        printf("UE %lu: frame index: %d, subframe index: %d not for RA\n", 
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
    printf("UE %lu: start RAO: %d, end RAO: %d\n",
            id,
            startRAO,
            endRAO);
    printf("subframe start RAO: %d, subframe end RAO: %d\n", 
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

    printf("raStartRAO: %d, raEndRAO: %d\n", raStartRAO, raEndRAO);
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
    printf("start preambe number: %d, number of preamble: %d\n", 
            startPreamble, 
            nPreambles);
    selectRAOIndex = getRnd(0, raos.size() - 1);
    selectPreambleIndex = getRnd(startPreamble, startPreamble + nPreambles - 1);
    printf("select rao: %d, select preamble: %d\n", 
            raos[selectRAOIndex], 
            selectPreambleIndex);
    candidateCell->receivePreamble(raos[selectRAOIndex], 
            selectPreambleIndex);
    preambleTransmitted = true;
}

// transmit Msg3
void UE::transmitMsg3(){
    Msg3 *msg3 = new Msg3;
    msg3->uplinkResourceIndex = uplinkResourceIndex;
    msg3->tc_rnti = tc_rnti;
    msg3->ueIndex = id;
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

// test whether ue RA already success 
bool UE::isRASuccess(){
    return raSuccess;
}

// draw ue
// painter: QPainter
void UE::drawUE(QPainter &painter){
    if(collided)
        painter.setBrush(QBrush(QColor(200, 0, 128, 255), Qt::SolidPattern));
    painter.drawEllipse(x - UEPixelSize / 2, 
            y - UEPixelSize / 2,
            UEPixelSize,
            UEPixelSize);
    if(collided)
        painter.setBrush(QBrush(QColor(200, 128, 255, 255), Qt::SolidPattern));
}

// get stored RAOs
// typicallly testing use this method
// other cell may NOT using this method
vector<int>& UE::getRAOs(){
    return raos;
}
