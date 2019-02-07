#include "PRACHConfig.h"

PRACHConfig::PRACHConfig(int prachConfigIndex){
    this->prachConfigIndex = prachConfigIndex;
}

PRACHConfig::~PRACHConfig(){
    delete[] nRASubframe;
}

void PRACHConfig::setPrachConfigIndex(int prachConfigIndex){
    this->prachConfigIndex = prachConfigIndex;
}

void PRACHConfig::setNumberofPrachSlot(int nPRACHSlot){
    this->nPRACHSlot = nPRACHSlot;
}

void PRACHConfig::setNumberofTimeDomainRAO(int nTimeDomainRAO){
    this->nTimeDomainRAO = nTimeDomainRAO;
}

int PRACHConfig::getPrachConfigIndex(){
    return this->prachConfigIndex;
}

int* PRACHConfig::getRASubframe(int *returnSize){
    *returnSize = sizeofRASubframe;
    return nRASubframe;
}

int PRACHConfig::getNumberofPRACHSlotinSubframe(){
    return this->nPRACHSlot;
}

int PRACHConfig::getNumberofTimeDomainRAO(){
    return this->nTimeDomainRAO;
}

