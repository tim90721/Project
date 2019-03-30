#include "MonitorRAFunction.h"

// constructor
// availiableRAO: need ssb per rao etc. parameter
// prachConfig: need RA configuration period etc. parameter
MonitorRAFunction::MonitorRAFunction(AvailiableRAO *availiableRAO, IPRACHConfig *prachConfig) :
    successUEs(0), failedUEs(0), raCount(0), 
    availiableRAO(availiableRAO), prachConfig(prachConfig){
    setbuf(stdout, NULL);
    tau = getTau();
    printf("tau: %d\n", tau);
    nSSB = availiableRAO->getNumberofSSB();
    ssbPerRAO = availiableRAO->getSSBPerRAO();
    delta = getDelta(availiableRAO->getNumberofPreambles(),
            availiableRAO->getSSBPerRAO());
    printf("delta: %f\n", delta);
}

// record ra ues condition
// success: successful ra ues in current subframe
// failed: failed ra ues in current subframe
void MonitorRAFunction::recordUEsCondition(const int success, const int failed){
    successUEs += success;
    failedUEs += failed;
    raCount++;
}

// update rao configurations
// TODO: complete comment
void MonitorRAFunction::updateRAOs(){
    printf("updating rao configurations\n");
    //if(raCount == 0 || successUEs == 0 /*will remove successUEs condition when predict function is complete*/)
    //    return;
    double totalDelta = delta * raCount;
    double estimateUEs = (double)successUEs * ssbPerRAO * exp(1);
    double newSSBPerRAO = calculateNewSSBPerRAO();
    int newMsg1FDM = getNewMsg1FDM(newSSBPerRAO);
    printf("old tau: %d\n", tau);
    printf("success ues: %lu\n", successUEs);
    printf("failed ues: %lu\n", failedUEs);
    printf("estimate ues: %f\n", estimateUEs);
    printf("total delta: %f\n", totalDelta);
    printf("old ssb per rao: %f\n", ssbPerRAO);
    printf("old msg1FDM: %d\n", availiableRAO->getMsg1FDM());
    availiableRAO->setSSBPerRAO(newSSBPerRAO);
    availiableRAO->setMsg1FDM(newMsg1FDM);
    availiableRAO->updateAssociationFrame();
    ssbPerRAO = newSSBPerRAO;
    tau = getTau();
    delta = getDelta(availiableRAO->getNumberofPreambles(), newSSBPerRAO);
    printf("new ssb per rao: %f\n", newSSBPerRAO);
    printf("new msg1FDM: %d\n", newMsg1FDM);
    successUEs = 0;
    failedUEs = 0;
    raCount = 0;
}

// get tau by current configuration
// return: tau
int MonitorRAFunction::getTau(){
    return getTau(prachConfig->getX(),
            availiableRAO->getTotalNeedRAO(),
            availiableRAO->getTotalRAOPerSubframe(),
            prachConfig->getNumberofRASubframe());
}

// get tau by the given configuration
// RAConfigPeriod: ra configuration period
// totalNeedRAO: total need raos for mapping all ssb once
// totalRAOPerSubframe: total raos in a subframe
// nRASubframe: number of ra subframe in a frame
// return: tau
int MonitorRAFunction::getTau(const int RAConfigPeriod, const int totalNeedRAO, const int totalRAOPerSubframe, const int nRASubframe){
    double ssbTotalNeedSubframe = (ceil((double)totalNeedRAO / (double)totalRAOPerSubframe))
        * ((double) (10 * RAConfigPeriod) / (double) nRASubframe);
    printf("total need subframe for mapping all ssb in period: %f\n",
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

// get new msg1-FDM
// ============================
// if ssb per rao get smaller, it need to check the tau is getting larger
// if so, msg1-FDM need to increase and not over 8 frequency-domain rao
// -----------------------
// if ssb per rao get larger, check when msg1-FDM modify 
// to a bit smaller can still get the same or smaller tau
// if so, msg1-FDM is modify to this value
// ============================
// newSSBPerRAO: the new ssb per rao value
// return: new msg1-FDM parameter
int MonitorRAFunction::getNewMsg1FDM(const double newSSBPerRAO){
    int newTau = getTau(prachConfig->getX(),
            nSSB / newSSBPerRAO,
            availiableRAO->getTotalRAOPerSubframe(),
            prachConfig->getNumberofRASubframe());
    int msg1FDM = availiableRAO->getMsg1FDM();
    int i = log(msg1FDM) / log(2);
    printf("msg1fdm index: %d\n", i);
    int newMsg1FDM = fRAO[i];
    if(newSSBPerRAO < ssbPerRAO && newTau > tau && newTau > 5 && msg1FDM < 8){
        while(newMsg1FDM < 8){
            int newTotalRAOPerSubframe = prachConfig->getNumberofTimeDomainRAO() * newMsg1FDM;
            newTau = getTau(prachConfig->getX(),
                    nSSB / newSSBPerRAO,
                    newTotalRAOPerSubframe,
                    prachConfig->getNumberofRASubframe());
            if(newTau <= tau)
                break;
            else{
                newMsg1FDM = fRAO[++i];
            }
        }
        if(newMsg1FDM == fRAO[3]){
            printf("msg1FDM reach maximum capacity\n");
        }
        else{
            newMsg1FDM = fRAO[++i];
        }
    }
    else if(newSSBPerRAO > ssbPerRAO){
        while(newMsg1FDM > 1){
            newMsg1FDM = fRAO[--i];
            int newTotalRAOPerSubframe = prachConfig->getNumberofTimeDomainRAO() * newMsg1FDM;
            newTau = getTau(prachConfig->getX(),
                    nSSB / newSSBPerRAO,
                    newTotalRAOPerSubframe,
                    prachConfig->getNumberofRASubframe());
            if(newTau > tau){
                newMsg1FDM = fRAO[++i];
                break;
            }
        }
        if(newMsg1FDM == fRAO[0])
            printf("msg1FDM reach minimum capacity\n");
    }
    printf("new tau: %d\n", newTau);
    return newMsg1FDM;
}

// get delta by given configuration
// nPreambles: number of CBRA preambles
// ssbPerRAO: ssb per rao
// return: delta
double MonitorRAFunction::getDelta(const int nPreambles, const double ssbPerRAO){
    //printf("nPreamble: %d\n", nPreambles);
    //printf("ssb per rao: %f\n", ssbPerRAO);
    double newDelta = ((double)(nPreambles * nSSB)) / (exp(1) * ssbPerRAO) 
        * ((double)(prachConfig->getNumberofTimeDomainRAO() * availiableRAO->getMsg1FDM()) / (double)availiableRAO->getTotalNeedRAO());
    printf("time domain raos: %d\n", prachConfig->getNumberofTimeDomainRAO());
    printf("msg1-FDM: %d\n", availiableRAO->getMsg1FDM());
    printf("total need raos: %d\n", availiableRAO->getTotalNeedRAO());
    return newDelta;
}

// calculate new ssb per rao based on success ues
// return: new ssb per rao
double MonitorRAFunction::calculateNewSSBPerRAO(){
    double newSSBPerRAO = (availiableRAO->getNumberofPreambles() * nSSB) / (successUEs * exp(1))
        * ((double)(prachConfig->getNumberofTimeDomainRAO() * availiableRAO->getMsg1FDM()) / (double)availiableRAO->getTotalNeedRAO());
    printf("new ssb per rao in double: %f\n", newSSBPerRAO);
    if(newSSBPerRAO > nSSB){
        return nSSB;
    }
    int i = 0;
    while(i < 7 && !(sRAO[i] <= newSSBPerRAO && newSSBPerRAO <= sRAO[i + 1]))
        i++;
    return sRAO[i];
}

// get success UEs
// return: success ues count
unsigned long MonitorRAFunction::getSuccessUEs(){
    return successUEs;
}

// get failed UEs
// return: failed ues count
unsigned long MonitorRAFunction::getFailedUEs(){
    return failedUEs;
}
