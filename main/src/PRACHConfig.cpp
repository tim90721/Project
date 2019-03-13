#include "PRACHConfig.h"

// constructor
// prachConfigIndex: corresponding to TS 38.331 prach-ConfigurationIndex
PRACHConfig::PRACHConfig(int prachConfigIndex){
    this->prachConfigIndex = prachConfigIndex;
}

////destructor
//PRACHConfig::~PRACHConfig(){
//}

// set prach-ConfigurationIndex
// and config RA parameters
// prachConfigIndex: cooresponding to TS 38.331 prach-ConfigurationIndex
void PRACHConfig::setPrachConfigIndex(int prachConfigIndex){
    this->prachConfigIndex = prachConfigIndex;
    configRA();
}

// set number of prach slot in a subframe
void PRACHConfig::setNumberofPrachSlot(int nPRACHSlot){
    this->nPRACHSlot = nPRACHSlot;
}

// set number of time domain RAO per prach slot
void PRACHConfig::setNumberofTimeDomainRAO(int nTimeDomainRAOPerPrachSlot){
    this->nTimeDomainRAOPerPrachSlot = nTimeDomainRAOPerPrachSlot;
}

// get prach-ConfigurationIndex
// return: prach-ConfigurationIndex
int PRACHConfig::getPrachConfigIndex(){
    return this->prachConfigIndex;
}

// get x, x corresponding to TS 38.211 6.3.3.2 table
int PRACHConfig::getX(){
    return x;
}

// get y, y corresponding to TS 38.211 6.3.3.2 table
int PRACHConfig::getY(){
    return y;
}

// get prach configuration period
// minimum is 10ms(1 frame)
// maximum is 160ms(16 frame)
// associated with SSB rate matching period
int PRACHConfig::getPrachConfigPeriod(){
    return this->prachConfigPeriod;
}

// get subframes that can perform RA
// return: each subframe can perform RA
vector<int>& PRACHConfig::getRASubframe(){
    return raSubframes;
}

// get number of prach slot in a subframe
// return: number of prach slot in a subframe
int PRACHConfig::getNumberofPRACHSlotinSubframe(){
    return this->nPRACHSlot;
}

// get number of time domain rao per prach slot
// return: number of time domain rao per prach slot
int PRACHConfig::getNumberofTimeDomainRAOPerPrachSlot(){
    return this->nTimeDomainRAOPerPrachSlot;
}

// get number of time domain rao in a subframe
// return: number of time domain rao in a subframe
int PRACHConfig::getNumberofTimeDomainRAO(){
    return (this->nTimeDomainRAOPerPrachSlot * this->nPRACHSlot);
}

// get number of subframe that can perform RA
// return: number of subframe that can perform RA
int PRACHConfig::getNumberofRASubframe(){
    return raSubframes.size();
}
