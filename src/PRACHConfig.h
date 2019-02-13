#ifndef PRACH_CONFIGURATION
#define PRACH_CONFIGURATION

#include "IPRACHConfig.h"

class PRACHConfig : IPRACHConfig{
    protected:
        int prachConfigIndex;
        int nPRACHSlot;
        int nTimeDomainRAOPerPrachSlot;
        int sizeofRASubframe;
        int *nRASubframe;
        int prachConfigPeriod;
    public:
        PRACHConfig(int prachConfigIndex);
        ~PRACHConfig();
        void setPrachConfigIndex(int prachConfigIndex);
        void setNumberofPrachSlot(int nPRACHSlot);
        void setNumberofTimeDomainRAO(int nTimeDomainRAO);
        int getPrachConfigIndex();
        int getPrachConfigPeriod();
        int* getRASubframe(int *returnSize);
        int getNumberofPRACHSlotinSubframe();
        int getNumberofTimeDomainRAOPerPrachSlot();
        int getNumberofTimeDomainRAO();
        int getNumberofRASubframe();
        virtual void configRA() = 0;
};
#endif
