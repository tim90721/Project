#ifndef MONITOR_RA_FUNCTION
#define MONITOR_RA_FUNCTION

#include "AvailiableRAO.h"
#include "IPRACHConfig.h"

#include <cmath>

class MonitorRAFunction{
    private:
        unsigned long successUEs;
        unsigned long failedUEs;
        int tau;
        int raCount;
        int nSSB;
        double coefThreshold;
        double ssbPerRAO;
        double delta;
        AvailiableRAO *availiableRAO;
        IPRACHConfig *prachConfig;

    public:
        MonitorRAFunction(AvailiableRAO *availiableRAO, IPRACHConfig *prachConfig);
        void recordUEsCondition(const int success, const int failed);
        void updateRAOs();
        int getTau();
};

#endif
