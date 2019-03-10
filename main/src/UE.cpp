#include "UE.h"

using namespace std;

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

void UE::receiveSI(Cell *cell){
    if(cell->getCellIndex() == this->cellIndex){
        // TODO: set ssb-perrach-OccasionAndCBRA-preambles
        // TODO: set CRE(future work)
        printf("UE %d receive cell index %d, beam index %d system information\n", 
                this->id,
                cell->getCellIndex(),
                beamIndex);
        this->candidateCell = cell;
        prachConfig = cell->getPRACHConfig();
        availiableRAO = cell->getAvailiableRAO();
        startRAO = beamIndex / availiableRAO->getSSBPerRAO();
        int nRAO = 1 / availiableRAO->getSSBPerRAO();
        if(nRAO > 0)
            nRAO -= 1;
        endRAO = startRAO + nRAO;
        return;
    }
    printf("Other cell is better, doesn't need to receive cell index %d SI\n", cell->getCellIndex());
}

void UE::doRA(){
    if(!preambleTransmitted){
        checkRA();
        if(raStartRAO != -1 && raEndRAO != -1){
            printf("current subframe is for UE %d RA\n", id);
            printf("UE %d: ra start RAO: %d\tra end RAO: %d\n", 
                    id,
                    raStartRAO,
                    raEndRAO);
            storeRAOsforRA(availiableRAO->getStartRAOofSubframe(),
                    availiableRAO->getEndRAOofSubframe());
            printf("number of rao: %d\n", raos.size());
            printf("rao index: ");
            for(unsigned int i = 0;i < raos.size();i++)
                printf("%4d", raos[i]);
            printf("\n");
            transmitMsg1();
        }
        else{
            printf("current subframe is not for UE %d RA\n", id);
        }
    }
    else if (preambleTransmitted && !msg3Transmitted){
        transmitMsg3();
    }
    else if(preambleTransmitted && msg3Transmitted && raSuccess){
        printf("RA already success, wait for remove from simulation\n");
    }
    else{
        printf("something wrong!!!\n");
    }
}

void UE::receiveRAR(const vector<RAR*>& rars){
    int index = searchRAR(rars, selectRAOIndex, selectPreambleIndex);
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
}

void UE::receiveCR(const vector<Msg3*>& CRs){
    int index = searchMsg3(CRs, tc_rnti);
    printf("contention resolution index: %d\n", index);
    printf("UE TC-RNTI: %d, searched TC-RNTI: %d\n",
            tc_rnti,
            CRs[index]->tc_rnti);
    printf("UE id: %d, searched UE id: %d\n",
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
    }
}

void UE::checkRA(){
    int frameIndex = candidateCell->getFrameIndex();
    int subframeIndex = candidateCell->getSubframeIndex();
    raos.clear();
    if(availiableRAO->isRASubframe(frameIndex, subframeIndex)){
        printf("UE %d: frame index: %d, subframe Index: %d is for RA\n",
                id,
                frameIndex,
                subframeIndex);
        updateRAOforRA();
    }
    else{
        printf("UE %d: frame index: %d, subframe index: %d not for RA\n", 
                id,
                frameIndex,
                subframeIndex);
        raStartRAO = -1;
        raEndRAO = -1;
    }
}

void UE::updateRAOforRA(){
    const int subframeStartRAO = availiableRAO->getStartRAOofSubframe();
    const int subframeEndRAO = availiableRAO->getEndRAOofSubframe();
    const int totalNeedRAO = availiableRAO->getTotalNeedRAO();
    printf("UE %d: start RAO: %d, end RAO: %d\n",
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

void UE::storeRAOsforRA(const int subframeStartRAO, const int subframeEndRAO){
    int nRAO = 1 / availiableRAO->getSSBPerRAO();
    const int totalNeedRAO = availiableRAO->getTotalNeedRAO();
    const int totalRAOPerSubframe = availiableRAO->getTotalRAOPerSubframe();

    printf("raStartRAO: %d, raEndRAO: %d\n", raStartRAO, raEndRAO);
    for(int i = 0;i < raEndRAO - raStartRAO + 1;i++){
        raos.push_back(raStartRAO + i);
    }
    
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
    //for(int i = 0;i < 50;i++){
    //    candidateCell->receivePreamble(raos[getRnd(0 , raos.size() - 1)], 
    //            getRnd(startPreamble, startPreamble + nPreambles - 1));
    //}
    preambleTransmitted = true;
}

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

bool UE::isBindCell(){
    if(candidateCell)
        return true;
    return false;
}

bool UE::isPreambleTransmit(){
    return preambleTransmitted;
}

bool UE::isRarReceived(){
    return rarReceived;
}

bool UE::isRASuccess(){
    return raSuccess;
}

// draw ue
// painter: QPainter
void UE::drawUE(QPainter &painter){
    painter.drawEllipse(x - UEPixelSize / 2, 
            y - UEPixelSize / 2,
            UEPixelSize,
            UEPixelSize);
}

vector<int>& UE::getRAOs(){
    return raos;
}
