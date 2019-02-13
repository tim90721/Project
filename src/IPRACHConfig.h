#ifndef IPRACH_CONFIGURATION
#define IPRACH_CONFIGURATION

class IPRACHConfig{
    public:
        virtual int getPrachConfigIndex() = 0;
        virtual int getPrachConfigPeriod() = 0;
        virtual int getNumberofPRACHSlotinSubframe() = 0;
        virtual int getNumberofTimeDomainRAOPerPrachSlot() = 0;
        virtual int getNumberofTimeDomainRAO() = 0;
        virtual int getNumberofRASubframe() = 0;
        virtual int* getRASubframe(int* returnSize) = 0;
};
#endif
