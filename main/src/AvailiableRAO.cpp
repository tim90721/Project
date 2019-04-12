#include "AvailiableRAO.h"

//AvailiableRAO::AvailiableRAO(int nSSB){
//    this->nSSB = nSSB;
//    printf("%f", this->ssbPerRAO);
//}

// constructor
// nSSB: number of ssb of the cell
// ssbPerRAO: corresponding to TS 38.331 ssb-perRACH-Occasion
// msg1FDM: corresponding to TS 38.331 msg1-FDM
// nPreambles: total number of availiable contention preambles can use per rao per cell
// ssbPeriod: corresponding to SSB rate matching period
// prachConfig: PrachConfig
AvailiableRAO::AvailiableRAO(int nSSB, double ssbPerRAO, int msg1FDM, int nPreambles, int ssbPeriod, IPRACHConfig *prachConfig) : nSSB(nSSB), nPreambles(nPreambles), ssbPeriod(ssbPeriod), prachConfig(prachConfig){
    setSSBPerRAO(ssbPerRAO);
    setMsg1FDM(msg1FDM);
    updateAssociationFrame();
}

// set number of ssb of a cell
// nSSB: number of ssb of a cell
void AvailiableRAO::setNumberofSSB(int nSSB){
    this->nSSB = nSSB;
}

// set msg1FDM
// and update the number of total rao persubframe and frame
// msg1FDM: corresponding to TS 38.331 msg1-FDM
void AvailiableRAO::setMsg1FDM(int msg1FDM){
    this->msg1FDM = msg1FDM;
    this->totalRAOPerSubframe = prachConfig->getNumberofTimeDomainRAO() * msg1FDM;
    this->totalRAOPerFrame = this->totalRAOPerSubframe * prachConfig->getNumberofRASubframe();
    //printf("number of time domain raos: %d\n", 
    //        prachConfig->getNumberofTimeDomainRAO());
    //printf("number of ra subframe: %d\n",
    //        prachConfig->getNumberofRASubframe());
}

// set number of contention preambles can use per rao per cell
// nPreambles: number of contention preambles
void AvailiableRAO::setNumberofPreambles(int nPreambles){
    this->nPreambles = nPreambles;
}

// set ssb period
// ssbPeriod: corresponding to SSB rate matching period
void AvailiableRAO::setSSBPeriod(int ssbPeriod){
    this->ssbPeriod = ssbPeriod;
}

// set ssb per rao
// ssbPerRAO: corresponding to TS 38.331 ssb-perRACH-Occasion
void AvailiableRAO::setSSBPerRAO(double ssbPerRAO){
    this->ssbPerRAO = ssbPerRAO;
    this->totalNeedRAO = this->nSSB / ssbPerRAO;
    if(totalNeedRAO == 0){
        SPDLOG_CRITICAL("ssb per rao: {0}", ssbPerRAO);
        SPDLOG_CRITICAL("nSSB: {0}", nSSB);
        SPDLOG_CRITICAL("total need rao: {0}", totalNeedRAO);
        SPDLOG_CRITICAL("total need rao should not be 0");
        exit(1);
    }
}

// update subframe start and end RAO of current subframe
// if current frame of subframe does not have enough RAO for mapping all SSB one more time
// startRAO and endRAO is -1
// frameIndex: frame index
// subframeIndex: subframe index
void AvailiableRAO::updateStartandEndRAOofSubframe(const int frameIndex, const int subframeIndex){
    SPDLOG_TRACE("updating rao of subframe");
    if(isRASubframe(frameIndex, subframeIndex)){
        SPDLOG_TRACE("next subframe is ra subframe");
        int frame = frameIndex % associationFrame;
        frame = frame / (prachConfig->getPrachConfigPeriod() / 10);
        startRAO = frame * totalRAOPerFrame;
        vector<int> RASubframe = prachConfig->getRASubframe();
        for(unsigned int i = 0;subframeIndex != RASubframe[i];i++)
            startRAO += totalRAOPerSubframe;
        SPDLOG_INFO("nSSB: {0}, msg1FDM: {1}, ssb per rao: {2}, time domain rao per subframe: {3}, ra subframe in a frame: {4}",
                nSSB,
                msg1FDM,
                ssbPerRAO,
                prachConfig->getNumberofTimeDomainRAO(),
                prachConfig->getNumberofRASubframe());
        if(associationFrame == 1){
            SPDLOG_INFO("association frame is 1");
            // when total rao per frame can map all ssb more than 1 time
            int times = totalRAOPerFrame / totalNeedRAO;
            if((startRAO / totalNeedRAO) >= times){
                // when remaining rao in the frame is not enough for 
                // mapping all ssb one more time
                // remaining rao can not use for RA
                // corresponding to TS 38.213 8.1
                startRAO = -1;
                endRAO = -1;
                return;
            }
            else{
                endRAO = startRAO + totalRAOPerSubframe - 1;
                if(endRAO / totalNeedRAO >= times){
                    // if endRAO is larger than total rao of a frame can support
                    // the endRAO is assigned to last RAO of this frame
                    endRAO = times * totalNeedRAO - 1;
                    startRAO %= totalNeedRAO;
                    endRAO %= totalNeedRAO;
                }
                else{
                    startRAO %= totalNeedRAO;
                    endRAO = startRAO + totalRAOPerSubframe - 1;
                }
                //printf("testing--->startRAO: %d, endRAO: %d\n", startRAO, endRAO);
                //printf("testing--->times: %d\n", times);
                return;
            }
        }
        else if(associationFrame > 1){
            SPDLOG_INFO("association frame is not 1");
            // a frame can not map all SSB to a RAO
            int times = 1;
            SPDLOG_WARN("start RAO: {0}", startRAO);
            SPDLOG_WARN("totalNeedRAO: {0}", totalNeedRAO);
            SPDLOG_WARN("end RAO: {0}", endRAO);
            SPDLOG_INFO("ssb per rao: {0}" , ssbPerRAO);
            if(startRAO / totalNeedRAO >= times){
                startRAO = -1;
                endRAO = -1;
                return;
            }
            SPDLOG_TRACE("start rao calculated");
            endRAO = startRAO + totalRAOPerSubframe - 1;
            if(endRAO / totalNeedRAO >= times)
                endRAO = times * totalNeedRAO - 1;
            SPDLOG_TRACE("end rao calculated");
        }
        //endRAO = startRAO + totalRAOPerSubframe - 1;
    }
    SPDLOG_TRACE("update complete");
}

// update association frame
// corresponding to TS 38.213 8.1
void AvailiableRAO::updateAssociationFrame(){
    // calculate association period for this PRACH configuration
    associationPeriod = (totalNeedRAO / totalRAOPerFrame);
    SPDLOG_INFO("totalNeedRAO: {0}, totalRAOPerFrame: {1}, totalRAOPerSubframe: {2}", 
            totalNeedRAO,
            totalRAOPerFrame,
            totalRAOPerSubframe);
    if(totalNeedRAO % totalRAOPerFrame)
        associationPeriod += 1;

    // total need frame for all ssb mapping to 
    // rao at least once 
    // associationFrame can only be 1, 2, 4, 8, 16
    associationFrame = (associationPeriod  * prachConfig->getPrachConfigPeriod() / 10);
    if(!(associationFrame == 1 
            || associationFrame == 2
            || associationFrame == 4
            || associationFrame == 8
            || associationFrame == 16)){
        int association = 2;
        while(associationFrame / association != 0){
            association *= 2;
        }
        associationFrame = association;
    }
    SPDLOG_INFO("associationFrame: {0}", associationFrame);
}

// get number of SSB of a cell
// return: number of SSB in a cell
int AvailiableRAO::getNumberofSSB(){
    return this->nSSB;
}

// get number of msg1-FDM
// return: msg1-FDM corresponding to TS 38.331 
int AvailiableRAO::getMsg1FDM(){
    return this->msg1FDM;
}

// get number of contention preambles per rao per cell
// return: number of contention preambles
int AvailiableRAO::getNumberofPreambles(){
    return this->nPreambles;
}

// get ssb period
// return: ssb period, corresponding to SSB rate matching period
int AvailiableRAO::getSSBPeriod(){
    return this->ssbPeriod;
}

// get start number of preamble can use for RA based on ssb index
// ssbIndex: the index of ssb
// return: the start index of preamble
int AvailiableRAO::getStartNumberofPreamble(int ssbIndex){
    if(this->ssbPerRAO > 1){
        int start = (ssbIndex % (int)ssbPerRAO) * (this->nPreambles / this->ssbPerRAO);
        return start;
    }
    else
        return 0;
}

// get start number of RAO can use for RA based on ssbIndex
// return: the start index of RAO can use
int AvailiableRAO::getStartNumberofRAO(int ssbIndex){
    return ssbIndex / this->ssbPerRAO;
}

// get start number of RAO for current subframe
// return: start number of RAO for current subframe
int AvailiableRAO::getStartRAOofSubframe(){
    return startRAO;
}

// get end number of RAO for current subframe
// return: end index of RAO for current subframe
int AvailiableRAO::getEndRAOofSubframe(){
    return endRAO;
}

// get total need RAO for mapping all SSB
// return: total need RAO
int AvailiableRAO::getTotalNeedRAO(){
    return totalNeedRAO;
}

// get total RAO of a subframe
// return: total RAO of a subframe
int AvailiableRAO::getTotalRAOPerSubframe(){
    return totalRAOPerSubframe;
}

// get ssb per rao
// return: ssb per rao, corresponding to TS 38.331
double AvailiableRAO::getSSBPerRAO(){
    return this->ssbPerRAO;
}

// check is this frame index and subframe index is 
// for this ssb index RA
// frameIndex: frame index
// subframeIndex: subframe index
// return true: if this subframe can perform RA
// otherwise false
bool AvailiableRAO::isRASubframe(const int frameIndex, const int subframeIndex){
    if(frameIndex % prachConfig->getX() != prachConfig->getY()){
        //printf("frame index: %d is not for RA\n", frameIndex);
        return false; 
    }
    vector<int> raSubframes = prachConfig->getRASubframe();
    if(!binary_search(raSubframes.begin(), raSubframes.end(), subframeIndex)){
        //printf("subframe index: %d isn't for RA\n", subframeIndex);
        return false;
    }
    return true;
}

// destructor
AvailiableRAO::~AvailiableRAO(){
}
