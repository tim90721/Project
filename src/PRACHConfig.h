#ifndef PRACH_CONFIGURATION
#define PRACH_CONFIGURATION

#include "IPRACHConfig.h"

class PRACHConfig : IPRACHConfig{
    protected:
        int prachConfigIndex;
        int nPRACHSlot;
        int nTimeDomainRAO;
        int sizeofRASubframe;
        int *nRASubframe;
    public:
        PRACHConfig(int prachConfigIndex);
        ~PRACHConfig();
        void setPrachConfigIndex(int prachConfigIndex);
        void setNumberofPrachSlot(int nPRACHSlot);
        void setNumberofTimeDomainRAO(int nTimeDomainRAO);
        int getPrachConfigIndex();
        int* getRASubframe(int *returnSize);
        int getNumberofPRACHSlotinSubframe();
        int getNumberofTimeDomainRAO();
        virtual void RAConfig();
};
#endif
