#include "PRACHConfigFR1Paired.h"

// constructor
// prachConfigIndex: corresponding to TS 38.331 prach-ConfigurationIndex
PRACHConfigFR1::PRACHConfigFR1(int prachConfigIndex) : PRACHConfig(prachConfigIndex){
}

// config ra parameters
void PRACHConfigFR1::configRA(){
    switch(prachConfigIndex){
        case 16:
            nPRACHSlot = 1;
            nTimeDomainRAOPerPrachSlot = 1;
            raSubframes.clear();
            raSubframes.push_back(1);
            prachConfigPeriod = 10;
            x = 1;
            y = 0;
            break;
        case 19:
            nPRACHSlot = 1;
            nTimeDomainRAOPerPrachSlot = 1;
            raSubframes.clear();
            raSubframes.push_back(1);
            raSubframes.push_back(6);
            prachConfigPeriod = 10;
            x = 1;
            y = 0;
            break;
        case 22:
            nPRACHSlot = 1;
            nTimeDomainRAOPerPrachSlot = 1;
            raSubframes.clear();
            raSubframes.push_back(1);
            raSubframes.push_back(4);
            raSubframes.push_back(7);
            prachConfigPeriod = 10;
            x = 1;
            y = 0;
            break;
        case 27:
            nPRACHSlot = 1;
            nTimeDomainRAOPerPrachSlot = 1;
            raSubframes.clear();
            for(int i = 0;i < 10;i++)
                raSubframes.push_back(i);
            prachConfigPeriod = 10;
            x = 1;
            y = 0;
            break;
        case 101:
            nPRACHSlot = 2;
            nTimeDomainRAOPerPrachSlot = 6;
            raSubframes.clear();
            raSubframes.push_back(1);
            prachConfigPeriod = 10;
            x = 1;
            y = 0;
            break;
        case 106:
            nPRACHSlot = 2;
            nTimeDomainRAOPerPrachSlot = 6;
            raSubframes.clear();
            for(int i = 0;i < 10;i++)
                raSubframes.push_back(i);
            prachConfigPeriod = 10;
            x = 1;
            y = 0;
            break;
        default:
            SPDLOG_CRITICAL("prach configuration %d not support\n", prachConfigIndex);
            exit(1);
    }
}

// destructor
PRACHConfigFR1::~PRACHConfigFR1(){
}
