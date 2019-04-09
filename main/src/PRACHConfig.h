#ifndef PRACH_CONFIGURATION
#define PRACH_CONFIGURATION

#include "IPRACHConfig.h"
#include "include_log.h"

class PRACHConfig : public IPRACHConfig{
    protected:
        int prachConfigIndex;
        int nPRACHSlot;
        int nTimeDomainRAOPerPrachSlot;
        int prachConfigPeriod;
        int x;
        int y;
        vector<int> raSubframes;
    public:
        PRACHConfig(int prachConfigIndex);
        void setPrachConfigIndex(int prachConfigIndex);
        void setNumberofPrachSlot(int nPRACHSlot);
        void setNumberofTimeDomainRAO(int nTimeDomainRAO);
        int getPrachConfigIndex();
        int getX();
        int getY();
        int getPrachConfigPeriod();
        vector<int>& getRASubframe();
        int getNumberofPRACHSlotinSubframe();
        int getNumberofTimeDomainRAOPerPrachSlot();
        int getNumberofTimeDomainRAO();
        int getNumberofRASubframe();
        virtual void configRA() = 0;
        virtual ~PRACHConfig();
};
#endif
