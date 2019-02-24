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
    this->candidateCell = NULL;
    startRAO = 0;
    endRAO = 0;
    raStartRAO = -1;
    raEndRAO = -1;
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
    }
    else{
        printf("current subframe is not for UE %d RA\n", id);
    }
}

void UE::checkRA(){
    int frameIndex = candidateCell->getFrameIndex();
    int subframeIndex = candidateCell->getSubframeIndex();
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
    int subframeStartRAO = availiableRAO->getStartRAOofSubframe();
    int subframeEndRAO = availiableRAO->getEndRAOofSubframe();
    printf("UE %d: start RAO: %d, end RAO: %d\n",
            id,
            startRAO,
            endRAO);
    printf("subframe start RAO: %d, subframe end RAO: %d\n", 
            availiableRAO->getStartRAOofSubframe(),
            availiableRAO->getEndRAOofSubframe());
    raStartRAO = startRAO;
    raEndRAO = endRAO;
    raos.clear();
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

//    if(raStartRAO == -1 || raEndRAO == -1)
//        return;
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
                //raEndRAO += nRAO;
            }
            else if(raStartRAO + nRAO > subframeEndRAO){
                raEndRAO = subframeEndRAO;
            }
            for(int i = 0;i < raEndRAO - raStartRAO + 1;i++)
                raos.push_back(raStartRAO + i);
        }
        // original
        //if(raStartRAO + totalNeedRAO < subframeEndRAO){
        //    raStartRAO += totalNeedRAO;
        //    if(raEndRAO + nRAO < subframeEndRAO){
        //        raEndRAO += nRAO;
        //    }
        //    else if(raEndRAO + nRAO > subframeEndRAO){
        //        raEndRAO = subframeEndRAO;
        //    }
        //    for(int i = 0;i < raEndRAO - raStartRAO + 1;i++)
        //        raos.push_back(raStartRAO + i);
        //}
    }
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

// draw ue
// painter: QPainter
void UE::drawUE(QPainter &painter){
    painter.drawEllipse(x - UEPixelSize / 2, 
            y - UEPixelSize / 2,
            UEPixelSize,
            UEPixelSize);
}

