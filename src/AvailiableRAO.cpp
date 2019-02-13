#include "AvailiableRAO.h"

//AvailiableRAO::AvailiableRAO(int nSSB){
//    this->nSSB = nSSB;
//    printf("%f", this->ssbPerRAO);
//}

AvailiableRAO::AvailiableRAO(int nSSB, double ssbPerRAO, int msg1FDM, int nPreambles, int ssbPeriod, IPRACHConfig *prachConfig){
    this->prachConfig = prachConfig;
    this->nPreambles = nPreambles;
    setNumberofSSB(nSSB);
    setSSBPerRAO(ssbPerRAO);
    setMsg1FDM(msg1FDM);
    setSSBPeriod(ssbPeriod);
}

void AvailiableRAO::setNumberofSSB(int nSSB){
    this->nSSB = nSSB;
}

void AvailiableRAO::setMsg1FDM(int msg1FDM){
    this->msg1FDM = msg1FDM;
    this->totalRAOPerSubframe = prachConfig->getNumberofTimeDomainRAO() * msg1FDM;
    this->totalRAOPerFrame = this->totalRAOPerSubframe * prachConfig->getNumberofRASubframe();
}

void AvailiableRAO::setNumberofPreambles(int nPreambles){
    this->nPreambles = nPreambles;
}

void AvailiableRAO::setSSBPeriod(int ssbPeriod){
    this->ssbPeriod = ssbPeriod;
}

void AvailiableRAO::setSSBPerRAO(double ssbPerRAO){
    this->ssbPerRAO = ssbPerRAO;
    this->totalNeedRAO = this->nSSB / ssbPerRAO;
}

int AvailiableRAO::getNumberofSSB(){
    return this->nSSB;
}

int AvailiableRAO::getMsg1FDM(){
    return this->msg1FDM;
}

int AvailiableRAO::getNumberofPreambles(){
    return this->nPreambles;
}

int AvailiableRAO::getSSBPeriod(){
    return this->ssbPeriod;
}

int AvailiableRAO::getStartNumberofPreamble(int ssbIndex){
    if(this->ssbPerRAO >= 1){
        int start = ssbIndex * (this->nPreambles / this->ssbPerRAO);
        return start;
    }
    else
        return 0;
}

int AvailiableRAO::getStartNumberofRAO(int ssbIndex){
    return ssbIndex / this->ssbPerRAO;
}

double AvailiableRAO::getSSBPerRAO(){
    return this->ssbPerRAO;
}

bool AvailiableRAO::isRASubframe(int frameIndex, int subframeIndex, int ssbIndex){
    int times;
    int raoIndex;
    if(totalNeedRAO > totalRAOPerFrame){
        // total need RAO for SSB mapping is lager than 1 frame of RAO
        // this implies that for all SSB mapping to RAO once
        // system needs more than 1 frame to complete
        times = totalNeedRAO / totalRAOPerFrame;
        raoIndex = getSSBPerRAO() * ssbIndex;
    }
    else{
        // total need RAO for SSB mapping is less than 1 frame of RAO
        // this implies that for all SSB mapping to RAO once
        // system needs less than 1 frame to accomplish
        // in other words, the total RAO in 1 frame
        // maybe can map SSB more than 1 time
    }
    return false;
}
