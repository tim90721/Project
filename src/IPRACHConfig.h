#ifndef IPRACH_CONFIGURATION
#define IPRACH_CONFIGURATION

class IPRACHConfig{
    public:
        virtual int* getRASubframe(int* returnSize);
        virtual int getNumberofPRACHSlotinSubframe();
        virtual int getNumberofTimeDomainRAO();
};
#endif
