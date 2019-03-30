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
        //double coefThreshold;
        double ssbPerRAO;
        double delta;
        const double sRAO[8] = {0.125, 0.25, 0.5, 1.0, 2.0, 4.0, 8.0, 16.0};
        const int fRAO[4] = {1, 2, 4, 8};
        AvailiableRAO *availiableRAO;
        IPRACHConfig *prachConfig;

        int getTau(const int RAConfigPeriod, const int totalNeedRAO, const int totalRAOPerSubframe, const int nRASubframe);
        int getNewMsg1FDM(const double newSSBPerRAO);
        double getDelta(const int nPreambles, const double ssbPerRAO);
        double calculateNewSSBPerRAO();

    public:
        MonitorRAFunction(AvailiableRAO *availiableRAO, IPRACHConfig *prachConfig);
        void recordUEsCondition(const int success, const int failed);
        void updateRAOs();
        int getTau();
        unsigned long getSuccessUEs();
        unsigned long getFailedUEs();
};

#endif
