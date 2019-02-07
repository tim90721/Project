#include "PRACHConfigFR1Paired.h"

PRACHConfigFR1::PRACHConfigFR1(int prachConfigIndex) : PRACHConfig(prachConfigIndex){
    configRA();
}

void PRACHConfigFR1::configRA(){
    switch(prachConfigIndex){
        case 16:
            nPRACHSlot = 1;
            nTimeDomainRAO = 1;
            sizeofRASubframe = 1;
            nRASubframe = new int[1];
            *nRASubframe = 1;
            break;
    }
}
