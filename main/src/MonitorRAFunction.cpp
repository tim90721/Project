#include "MonitorRAFunction.h"

// constructor
// availiableRAO: need ssb per rao etc. parameter
// prachConfig: need RA configuration period etc. parameter
MonitorRAFunction::MonitorRAFunction(AvailiableRAO *availiableRAO, IPRACHConfig *prachConfig) :
    successUEs(0), failedUEs(0), raCount(0), estimateUEs(0),
    availiableRAO(availiableRAO), prachConfig(prachConfig){
    //setbuf(stdout, NULL);
    tau = getTau();
    SPDLOG_DEBUG("tau: {0}", tau);
    nSSB = availiableRAO->getNumberofSSB();
    ssbPerRAO = availiableRAO->getSSBPerRAO();
    delta = getDelta(availiableRAO->getNumberofPreambles(),
            availiableRAO->getSSBPerRAO());
    SPDLOG_DEBUG("delta: {0}", delta);
}

// record ra ues condition
// success: successful ra ues in current subframe
// failed: failed ra ues in current subframe
void MonitorRAFunction::recordUEsCondition(const int success, const int failed){
    successUEs += success;
    failedUEs += failed;
    historySlot.push_back(success);
    raCount++;
}

// update rao configurations
// TODO: complete comment
void MonitorRAFunction::updateRAOs(){
    SPDLOG_TRACE("updating rao configurations\n");
    //if(raCount == 0 || successUEs == 0 /*will remove successUEs condition when predict function is complete*/)
    //    return;
    history.push_back(successUEs);
    estimateUEs = estimateNextUEsBySlot();
    double totalDelta = delta * raCount;
    //double estimateUEs = (double)successUEs * ssbPerRAO * exp(1);
    double newSSBPerRAO = calculateNewSSBPerRAO();
    int newMsg1FDM = getNewMsg1FDMver2(&newSSBPerRAO);
    SPDLOG_TRACE("old tau: {0}", tau);
    SPDLOG_TRACE("success ues: {0}", successUEs);
    SPDLOG_TRACE("failed ues: {0}", failedUEs);
    //SPDLOG_TRACE("estimate ues: {0}", estimateUEs);
    SPDLOG_TRACE("total delta: {0}", totalDelta);
    SPDLOG_TRACE("old ssb per rao: {0}", ssbPerRAO);
    SPDLOG_TRACE("old msg1FDM: {0}", availiableRAO->getMsg1FDM());
    SPDLOG_WARN("new ssb per rao: {0}", newSSBPerRAO);
    SPDLOG_TRACE("new msg1FDM: {0}", newMsg1FDM);
    availiableRAO->setSSBPerRAO(newSSBPerRAO);
    availiableRAO->setMsg1FDM(newMsg1FDM);
    availiableRAO->updateAssociationFrame();
    ssbPerRAO = newSSBPerRAO;
    tau = getTau();
    delta = getDelta(availiableRAO->getNumberofPreambles(), newSSBPerRAO);
    successUEs = 0;
    failedUEs = 0;
    raCount = 0;
}

// restore ssb per rao and msg1-fdm to 1
void MonitorRAFunction::restore2Initial(){
    availiableRAO->setSSBPerRAO(initSSBPerRAO);
    availiableRAO->setMsg1FDM(initMsg1FDM);
    availiableRAO->updateAssociationFrame();
    ssbPerRAO = initSSBPerRAO;
    tau = getTau();
    SPDLOG_WARN("tau: {0}", tau);
    delta = getDelta(availiableRAO->getNumberofPreambles(),
            availiableRAO->getSSBPerRAO());
    successUEs = 0;
    failedUEs = 0;
    estimateUEs = 0;
    raCount = 0;
    historySlot.erase(historySlot.begin(), historySlot.end());
    history.erase(history.begin(), history.end());
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
    SPDLOG_TRACE("total need subframe for mapping all ssb in period: {0}",
            ssbTotalNeedSubframe);
    if(ssbTotalNeedSubframe > 10){
        return (pow(2, ceil(log(ssbTotalNeedSubframe / 10.0) / log(2))) * 10);
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
    SPDLOG_TRACE("msg1fdm index: {0}", i);
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
            SPDLOG_INFO("msg1FDM reach maximum capacity\n");
        }
        // method 1 improved
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
            SPDLOG_INFO("msg1FDM reach minimum capacity\n");
    }
    SPDLOG_TRACE("new tau: {0}", newTau);
    return newMsg1FDM;
}

int MonitorRAFunction::getNewMsg1FDMver2(double *newSSBPerRAO){
    int newTau = getTau(prachConfig->getX(),
            nSSB / *newSSBPerRAO,
            availiableRAO->getTotalRAOPerSubframe(),
            prachConfig->getNumberofRASubframe());
    SPDLOG_TRACE("new tau: {0}", newTau);
    int msg1FDM = availiableRAO->getMsg1FDM();
    int i = log(msg1FDM) / log(2);
    SPDLOG_TRACE("msg1fdm index: {0}", i);
    double newMsg1FDM = pow(2, i);
    if(*newSSBPerRAO < ssbPerRAO && newTau > tau && newTau > 5 && msg1FDM < 8){
        newMsg1FDM = (((double)(estimateUEs * ssbPerRAO * exp(1)))
            / ((double)availiableRAO->getNumberofPreambles() * nSSB))
            * (((double)availiableRAO->getTotalNeedRAO())
            / ((double)prachConfig->getNumberofTimeDomainRAO() * raCount));
        SPDLOG_TRACE("new msg1FDM in double: {0}", newMsg1FDM);
        newMsg1FDM = pow(2, ceil(log(newMsg1FDM) / log(2)));
        SPDLOG_TRACE("new msg1FDM: {0}", newMsg1FDM);
        *newSSBPerRAO = ssbPerRAO;
        if(newMsg1FDM > 8){
            *newSSBPerRAO = (((double)availiableRAO->getNumberofPreambles() * nSSB)
                / ((double)estimateUEs * exp(1)))
                * (((double)prachConfig->getNumberofTimeDomainRAO() * newMsg1FDM)
                / (double)availiableRAO->getTotalNeedRAO())
                * raCount;

            //////////// should be more elegent ////////////
            if(*newSSBPerRAO > nSSB && nSSB != 64){
                SPDLOG_WARN("new ssb per rao is larger than nSSB");
                SPDLOG_WARN("new ssb per rao: {0}", *newSSBPerRAO);
                *newSSBPerRAO = nSSB;
            }
            if(sRAO[0] > *newSSBPerRAO){
                SPDLOG_INFO("maximum ssb per rao reached");
                *newSSBPerRAO = sRAO[0];
            }
            int i = 0;
            while(i < 7 && !(sRAO[i] <= *newSSBPerRAO && *newSSBPerRAO <= sRAO[i + 1]))
                i++;
            SPDLOG_WARN("new ssb per rao: {0}", sRAO[i]);
            *newSSBPerRAO = sRAO[i];
            //////////// should be more elegent ////////////

            SPDLOG_TRACE("new ssb per rao: {0}", *newSSBPerRAO);
            SPDLOG_INFO("msg1-FDM reach maximum capacity");
            newMsg1FDM = 8;
        }
    }
    else if(*newSSBPerRAO > ssbPerRAO){
        while(newMsg1FDM > 1){
            newMsg1FDM = pow(2, --i);
            int newTotalRAOPerSubframe = prachConfig->getNumberofTimeDomainRAO() * newMsg1FDM;
            newTau = getTau(prachConfig->getX(),
                    nSSB / *newSSBPerRAO,
                    newTotalRAOPerSubframe,
                    prachConfig->getNumberofRASubframe());
            if(newTau > tau){
                newMsg1FDM = pow(2, ++i);
                break;
            }
        }
        if(i == 0)
            SPDLOG_INFO("msg1FDM reach minimum capacity\n");
    }
    SPDLOG_TRACE("new tau: {0}", newTau);
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
    SPDLOG_TRACE("time domain raos: {0}", prachConfig->getNumberofTimeDomainRAO());
    SPDLOG_TRACE("msg1-FDM: {0}", availiableRAO->getMsg1FDM());
    SPDLOG_TRACE("total need raos: {0}", availiableRAO->getTotalNeedRAO());
    return newDelta;
}

// calculate new ssb per rao based on success ues
// return: new ssb per rao
double MonitorRAFunction::calculateNewSSBPerRAO(){
    double newSSBPerRAO = (availiableRAO->getNumberofPreambles() * nSSB) / (estimateUEs * exp(1))
        * ((double)(prachConfig->getNumberofTimeDomainRAO() * availiableRAO->getMsg1FDM()) / (double)availiableRAO->getTotalNeedRAO()) * raCount;
    SPDLOG_TRACE("new ssb per rao in double: {0}", newSSBPerRAO);
    if(newSSBPerRAO > nSSB && nSSB != 64){
        SPDLOG_WARN("new ssb per rao is larger than nSSB");
        SPDLOG_WARN("new ssb per rao: {0}", newSSBPerRAO);
        return nSSB;
    }
    if(sRAO[0] > newSSBPerRAO){
        SPDLOG_INFO("maximum ssb per rao reached\n");
        return sRAO[0];
    }
    int i = 0;
    while(i < 7 && !(sRAO[i] <= newSSBPerRAO && newSSBPerRAO <= sRAO[i + 1]))
        i++;
    SPDLOG_WARN("new ssb per rao: {0}", sRAO[i]);
    return sRAO[i];
}

// estimate next period's arrival ues by AR
unsigned long MonitorRAFunction::estimateNextUEsBySIBPeriod(){
    if(history.size() <= 1){
        SPDLOG_WARN("history is not enough, return first slot success UEs");
        return successUEs;
    }
    //if(historySlot.size() > raCount * 3){
    //    SPDLOG_WARN("history maximum size reached");
    //    SPDLOG_WARN("historySlot size: {0}", historySlot.size());
    //    historySlot.erase(historySlot.begin(), historySlot.begin() + raCount);
    //    SPDLOG_WARN("historySlot size: {0}", historySlot.size());
    //}
    double average = 0;
    for(auto it = history.begin();it != history.end();it++)
        average += (*it);
    average /= history.size();
    SPDLOG_INFO("success ues: {0}", successUEs);
    SPDLOG_INFO("average: {0}", average);
    long double numerator = 0;
    long double denominator = 0;
    for(decltype(history.size()) i = history.size() - 1;i > 0;--i){
        SPDLOG_WARN("i: {0}", i);
        numerator += (history[i] - average) * (history[i - 1] - average);
        denominator += pow((history[i] - average), 2);
    }
    double beta = numerator / denominator;
    SPDLOG_WARN("beta: {0}", beta);
    auto yt = history.back() - average;
    double estimate = yt * beta + average;
    SPDLOG_WARN("estimate ues: {0}", estimateUEs);
    return estimate;
}

// estimate next period's arrival ues by AR
unsigned long MonitorRAFunction::estimateNextUEsBySlot(){
    if(historySlot.size() <= 1){
        SPDLOG_WARN("historySlot is not enough, return first slot success UEs");
        return successUEs;
    }
    if(historySlot.size() > raCount * 2){
        SPDLOG_WARN("ra count: {0}", raCount);
        SPDLOG_WARN("history maximum size reached");
        SPDLOG_WARN("historySlot size: {0}", historySlot.size());
        historySlot.erase(historySlot.begin(), historySlot.begin() + raCount);
        SPDLOG_WARN("historySlot size: {0}", historySlot.size());
    }
    double average = 0;
    for(auto it = historySlot.begin();it != historySlot.end();it++)
        average += (*it);
    average /= historySlot.size();
    SPDLOG_INFO("success ues: {0}", successUEs);
    SPDLOG_INFO("average: {0}", average);
    long double numerator = 0;
    long double denominator = 0;
    for(decltype(historySlot.size()) i = historySlot.size() - 1;i > 0;--i){
        //SPDLOG_WARN("i: {0}", i);
        numerator += (historySlot[i] - average) * (historySlot[i - 1] - average);
        denominator += pow((historySlot[i] - average), 2);
    }
    double beta = numerator / denominator;
    SPDLOG_WARN("beta: {0}", beta);
    if(beta > 1){
        SPDLOG_WARN("beta > 1, fix beta to 1");
        beta = 1;
    }
    else if(beta < -1){
        SPDLOG_WARN("beta < -1, fix beta to -1");
        beta = -1;
    }
    auto yt = historySlot.back() - average;
    SPDLOG_WARN("yt: {0}", yt);
    long double estimate = 0;
    SPDLOG_WARN("ra count: {0}", raCount);
    for(int i = 0;i < raCount;++i){
        estimate = estimate + yt * beta + average;
        beta *= beta;
        SPDLOG_WARN("estimate ues: {0}", estimate);
    }
    SPDLOG_WARN("estimate ues: {0}", estimate);
    return estimate;
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

// get estimate UEs
// return: estimate ues
double MonitorRAFunction::getEstimateUEs(){
    return estimateUEs;
}
