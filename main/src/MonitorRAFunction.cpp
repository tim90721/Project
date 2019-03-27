#include "MonitorRAFunction.h"

MonitorRAFunction::MonitorRAFunction(AvailiableRAO *availiableRAO, IPRACHConfig *prachConfig) :
    successUEs(0), failedUEs(0), raCount(0), coefThreshold(0.8),
    availiableRAO(availiableRAO), prachConfig(prachConfig){
    tau = getTau();
    printf("tau: %d\n", tau);
    nSSB = availiableRAO->getNumberofSSB();
    delta = ((double)(availiableRAO->getNumberofPreambles() * nSSB))
        / ((double)tau * exp(1) * availiableRAO->getSSBPerRAO());
    printf("delta: %f\n", delta);
}

void MonitorRAFunction::recordUEsCondition(const int success, const int failed){
    successUEs += success;
    failedUEs += failed;
    raCount++;
}

void MonitorRAFunction::updateRAOs(){
    double totalDelta = delta * raCount;
    if(successUEs > coefThreshold * totalDelta){
        printf("channel capacity is reaching, updating RAO configuration\n");
    }
    raCount = 0;
}

int MonitorRAFunction::getTau(){
    int RAConfigPeriod = prachConfig->getX();
    double ssbTotalNeedSubframe = (ceil((double)availiableRAO->getTotalNeedRAO() / (double)availiableRAO->getTotalRAOPerSubframe()))
        * ((double)10 * RAConfigPeriod / (double)prachConfig->getNumberofRASubframe());
    printf("total need subframe for mapping all ssb: %f\n",
            ssbTotalNeedSubframe);
    if(ssbTotalNeedSubframe > 10){
        return (ceil(log(ssbTotalNeedSubframe / 10.0) / log(2)) * 10);
    }
    else if(ssbTotalNeedSubframe <= 5){
        return ceil(ssbTotalNeedSubframe);
    }
    else{
        return 10;
    }
}
