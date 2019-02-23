#include "PRACHConfig.h"

PRACHConfig::PRACHConfig(int prachConfigIndex){
    this->prachConfigIndex = prachConfigIndex;
}

PRACHConfig::~PRACHConfig(){
}

void PRACHConfig::setPrachConfigIndex(int prachConfigIndex){
    this->prachConfigIndex = prachConfigIndex;
}

void PRACHConfig::setNumberofPrachSlot(int nPRACHSlot){
    this->nPRACHSlot = nPRACHSlot;
}

void PRACHConfig::setNumberofTimeDomainRAO(int nTimeDomainRAOPerPrachSlot){
    this->nTimeDomainRAOPerPrachSlot = nTimeDomainRAOPerPrachSlot;
}

int PRACHConfig::getPrachConfigIndex(){
    return this->prachConfigIndex;
}

int PRACHConfig::getX(){
    return x;
}

int PRACHConfig::getY(){
    return y;
}

int PRACHConfig::getPrachConfigPeriod(){
    return this->prachConfigPeriod;
}

vector<int>& PRACHConfig::getRASubframe(){
    return raSubframes;
}

int PRACHConfig::getNumberofPRACHSlotinSubframe(){
    return this->nPRACHSlot;
}

int PRACHConfig::getNumberofTimeDomainRAOPerPrachSlot(){
    return this->nTimeDomainRAOPerPrachSlot;
}

int PRACHConfig::getNumberofTimeDomainRAO(){
    return (this->nTimeDomainRAOPerPrachSlot * this->nPRACHSlot);
}

int PRACHConfig::getNumberofRASubframe(){
    return raSubframes.size();
}
