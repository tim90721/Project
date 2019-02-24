#ifndef IPRACH_CONFIGURATION
#define IPRACH_CONFIGURATION

#include "includefile.h"

class IPRACHConfig{
    public:
        virtual int getPrachConfigIndex() = 0;
        virtual int getX() = 0;
        virtual int getY() = 0;
        virtual int getPrachConfigPeriod() = 0;
        virtual int getNumberofPRACHSlotinSubframe() = 0;
        virtual int getNumberofTimeDomainRAOPerPrachSlot() = 0;
        virtual int getNumberofTimeDomainRAO() = 0;
        virtual int getNumberofRASubframe() = 0;
        virtual vector<int>& getRASubframe() = 0;
};
#endif
