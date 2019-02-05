#include "AvailiableRAO.h"

AvailiableRAO::AvailiableRAO(){
    this->nSSB = 1;
    this->msg1FDM = 1;
    this->nPreambles = 64;
    this->ssbPerRAO = 1 / 4;
    printf("%f", this->ssbPerRAO);
}

AvailiableRAO::AvailiableRAO(int nSSB, int msg1FDM, int nPreambles, double ssbPerRAO){
    this->nSSB = nSSB;
    this->msg1FDM = msg1FDM;
    this->nPreambles = nPreambles;
    this->ssbPerRAO = ssbPerRAO;
}

void AvailiableRAO::setNumberofSSB(int nSSB){
    this->nSSB = nSSB;
}

void AvailiableRAO::setMsg1FDM(int msg1FDM){
    this->msg1FDM = msg1FDM;
}

void AvailiableRAO::setNumberofPreambles(int nPreambles){
    this->nPreambles = nPreambles;
}

void AvailiableRAO::setSSBPerRAO(double ssbPerRAO){
    this->ssbPerRAO = ssbPerRAO;
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
