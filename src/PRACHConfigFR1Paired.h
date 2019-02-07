#ifndef PRACH_CONFIGURATION_FR1_PAIRED
#define PRACH_CONFIGURATION_FR1_PAIRED

#include "PRACHConfig.h"

class PRACHConfigFR1 : PRACHConfig{
    private:
        int a;
    public:
        PRACHConfigFR1(int prachConfigIndex);
        ~PRACHConfigFR1();
        void configRA();
};
#endif
