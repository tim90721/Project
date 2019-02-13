#include "PRACHConfigFR1Paired.h"

PRACHConfigFR1::PRACHConfigFR1(int prachConfigIndex) : PRACHConfig(prachConfigIndex){
    configRA();
}

void PRACHConfigFR1::configRA(){
    switch(prachConfigIndex){
        case 16:
            nPRACHSlot = 1;
            nTimeDomainRAOPerPrachSlot = 1;
            sizeofRASubframe = 1;
            nRASubframe = new int[1];
            *nRASubframe = 1;
            prachConfigPeriod = 10;
            break;
        case 27:
            nPRACHSlot = 1;
            nTimeDomainRAOPerPrachSlot = 1;
            sizeofRASubframe = 10;
            nRASubframe = new int[10];
            for(int i = 0;i < 10;i++)
                nRASubframe[i] = i;
            prachConfigPeriod = 10;
            break;
        case 101:
            nPRACHSlot = 2;
            nTimeDomainRAOPerPrachSlot = 6;
            sizeofRASubframe = 1;
            nRASubframe = new int [1];
            nRASubframe[0] = 4;
            prachConfigPeriod = 10;
            break;
        case 106:
            nPRACHSlot = 2;
            nTimeDomainRAOPerPrachSlot = 6;
            sizeofRASubframe = 10;
            nRASubframe = new int[10];
            for(int i = 0;i < 10;i++)
                nRASubframe[i] = i;
            prachConfigPeriod = 10;
            break;
    }
}
