#include "PRACHConfigFR1Paired.h"

PRACHConfigFR1::PRACHConfigFR1(int prachConfigIndex) : PRACHConfig(prachConfigIndex){
    configRA();
}

void PRACHConfigFR1::configRA(){
    switch(prachConfigIndex){
        case 16:
            nPRACHSlot = 1;
            nTimeDomainRAOPerPrachSlot = 1;
            raSubframes.clear();
            raSubframes.push_back(1);
            //sizeofRASubframe = 1;
            //nRASubframe = new int[1];
            //*nRASubframe = 1;
            prachConfigPeriod = 10;
            x = 1;
            y = 0;
            break;
        case 27:
            nPRACHSlot = 1;
            nTimeDomainRAOPerPrachSlot = 1;
            //sizeofRASubframe = 10;
            //nRASubframe = new int[10];
            //for(int i = 0;i < 10;i++)
            //    nRASubframe[i] = i;
            for(int i = 0;i < 10;i++)
                raSubframes.push_back(i);
            prachConfigPeriod = 10;
            x = 1;
            y = 0;
            break;
        case 101:
            nPRACHSlot = 2;
            nTimeDomainRAOPerPrachSlot = 6;
            //sizeofRASubframe = 1;
            //nRASubframe = new int [1];
            //nRASubframe[0] = 4;
            raSubframes.push_back(4);
            prachConfigPeriod = 10;
            x = 1;
            y = 0;
            break;
        case 106:
            nPRACHSlot = 2;
            nTimeDomainRAOPerPrachSlot = 6;
            //sizeofRASubframe = 10;
            //nRASubframe = new int[10];
            //for(int i = 0;i < 10;i++)
            //    nRASubframe[i] = i;
            for(int i = 0;i < 10;i++)
                raSubframes.push_back(i);
            prachConfigPeriod = 10;
            x = 1;
            y = 0;
            break;
        default:
            printf("prach configuration %d not support\n", prachConfigIndex);
    }
}