#include "AvailiableRAO.h"

//AvailiableRAO::AvailiableRAO(int nSSB){
//    this->nSSB = nSSB;
//    printf("%f", this->ssbPerRAO);
//}

AvailiableRAO::AvailiableRAO(int nSSB, double ssbPerRAO, int msg1FDM, int nPreambles, int ssbPeriod, IPRACHConfig *prachConfig) : nSSB(nSSB), nPreambles(nPreambles), ssbPeriod(ssbPeriod), prachConfig(prachConfig){
    //this->prachConfig = prachConfig;
    //this->nPreambles = nPreambles;
    //setNumberofSSB(nSSB);
    setSSBPerRAO(ssbPerRAO);
    setMsg1FDM(msg1FDM);
    //setSSBPeriod(ssbPeriod);
    updateAssociationFrame();
}

void AvailiableRAO::setNumberofSSB(int nSSB){
    this->nSSB = nSSB;
}

void AvailiableRAO::setMsg1FDM(int msg1FDM){
    this->msg1FDM = msg1FDM;
    this->totalRAOPerSubframe = prachConfig->getNumberofTimeDomainRAO() * msg1FDM;
    this->totalRAOPerFrame = this->totalRAOPerSubframe * prachConfig->getNumberofRASubframe();
    //printf("number of time domain raos: %d\n", 
    //        prachConfig->getNumberofTimeDomainRAO());
    //printf("number of ra subframe: %d\n",
    //        prachConfig->getNumberofRASubframe());
}

void AvailiableRAO::setNumberofPreambles(int nPreambles){
    this->nPreambles = nPreambles;
}

void AvailiableRAO::setSSBPeriod(int ssbPeriod){
    this->ssbPeriod = ssbPeriod;
}

void AvailiableRAO::setSSBPerRAO(double ssbPerRAO){
    this->ssbPerRAO = ssbPerRAO;
    this->totalNeedRAO = this->nSSB / ssbPerRAO;
}

void AvailiableRAO::updateStartandEndRAOofSubframe(const int frameIndex, const int subframeIndex){
    if(isRASubframe(frameIndex, subframeIndex)){
        int frame = frameIndex % associationFrame;
        frame = frame / (prachConfig->getPrachConfigPeriod() / 10);
        startRAO = frame * totalRAOPerFrame;
        vector<int> RASubframe = prachConfig->getRASubframe();
        for(unsigned int i = 0;subframeIndex != RASubframe[i];i++)
            startRAO += totalRAOPerSubframe;
        if(associationFrame == 1){
            int times = totalRAOPerFrame / totalNeedRAO;
            if((startRAO / totalNeedRAO) >= times){
                startRAO = -1;
                endRAO = -1;
                return;
            }
            else{
                startRAO %= totalNeedRAO;
                endRAO = startRAO + totalRAOPerSubframe - 1;
                //printf("testing--->startRAO: %d, endRAO: %d\n", startRAO, endRAO);
                if(endRAO / totalNeedRAO >= times)
                    endRAO = times * totalNeedRAO - 1;
                return;
            }
        }
        else if(associationFrame > 1){
            int times = 1;
            if(startRAO / totalNeedRAO >= times){
                startRAO= -1;
                endRAO = -1;
                return;
            }
            endRAO = startRAO + totalRAOPerSubframe - 1;
            if(endRAO / totalNeedRAO >= times)
                endRAO = times * totalNeedRAO - 1;
        }
        //endRAO = startRAO + totalRAOPerSubframe - 1;
    }
}

void AvailiableRAO::updateAssociationFrame(){
    // calculate association period for this PRACH configuration
    //associationPeriod = ((totalNeedRAO / totalRAOPerFrame) + 1) *
    //    prachConfig->getPrachConfigPeriod();
    associationPeriod = (totalNeedRAO / totalRAOPerFrame);
    printf("totalNeedRAO: %d\ntotalRAOPerFrame: %d\ntotalRAOPerSubframe: %d\n", 
            totalNeedRAO,
            totalRAOPerFrame,
            totalRAOPerSubframe);
    if(totalNeedRAO % totalRAOPerFrame)
        associationPeriod += 1;
    // total need frame for all ssb mapping to 
    // rao at least once 
    associationFrame = (associationPeriod  * prachConfig->getPrachConfigPeriod() / 10);
    printf("associationFrame: %d\n", associationFrame);
}

int AvailiableRAO::getNumberofSSB(){
    return this->nSSB;
}

int AvailiableRAO::getMsg1FDM(){
    return this->msg1FDM;
}

int AvailiableRAO::getNumberofPreambles(){
    return this->nPreambles;
}

int AvailiableRAO::getSSBPeriod(){
    return this->ssbPeriod;
}

int AvailiableRAO::getStartNumberofPreamble(int ssbIndex){
    if(this->ssbPerRAO >= 1){
        int start = ssbIndex * (this->nPreambles / this->ssbPerRAO);
        return start;
    }
    else
        return 0;
}

int AvailiableRAO::getStartNumberofRAO(int ssbIndex){
    return ssbIndex / this->ssbPerRAO;
}

int AvailiableRAO::getStartRAOofSubframe(){
    return startRAO;
}

int AvailiableRAO::getEndRAOofSubframe(){
    return endRAO;
}

int AvailiableRAO::getTotalNeedRAO(){
    return totalNeedRAO;
}

int AvailiableRAO::getTotalRAOPerSubframe(){
    return totalRAOPerSubframe;
}

double AvailiableRAO::getSSBPerRAO(){
    return this->ssbPerRAO;
}

// check is this frame index and subframe index is 
// for this ssb index RA
// frameIndex: frame index
// subframeIndex: subframe index
// ssbIndex: ssb index
// return: start number of rao can use for this ssb in this subframe
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
    // calculate start rao index for ssb index
    //int raoIndex = ssbIndex / getSSBPerRAO(); 
    //int frame = frameIndex;     // copy of frameIndex
    
    //if(totalNeedRAO > totalRAOPerFrame){
    //    // total need RAO for SSB mapping is lager than 1 frame of RAO
    //    // this implies that for all SSB mapping to RAO once
    //    // system needs more than 1 frame to complete
    //    
    //    // calculate association period for this PRACH configuration
    //    int associationPeriod = (totalNeedRAO / totalRAOPerFrame) *
    //        prachConfig->getPrachConfigPeriod();
    //    // total need frame for all ssb mapping to 
    //    // rao at least once 
    //    int associationFrame = (associationPeriod / 10) + 1;
    //    // mod frame index with total need frame for all ssb mapping
    //    frameIndex %= associationFrame;
    //    // start rao index locate frame number
    //    int raStartFrameIndex = (raoIndex / totalRAOPerFrame) * 
    //        (prachConfig->getPrachConfigPeriod() / 10);
    //    int raEndFrameIndex = (raoIndex + ((1 / ssbPerRAO))
    //            / totalRAOPerFrame) *
    //        (prachConfig->getPrachConfigPeriod() / 10);
    //    // start ra subframe index
    //    int raStartSubframeIndex = (raoIndex / totalRAOPerSubframe); 
    //    int accumulationRAO = (frameIndex - 1) * totalRAOPerFrame;
    //    int i = 0;
    //    while(raSubframes.at(i) <= subframeIndex){
    //        accumulationRAO += totalRAOPerSubframe;
    //    }
    //    if((accumulationRAO <= raoIndex 
    //                && (accumulationRAO + totalRAOPerSubframe) >= raoIndex)
    //            || (accumulationRAO <= raoIndex + (1 / ssbPerRAO) 
    //                && (accumulationRAO + totalRAOPerSubframe) >= raoIndex + (1 / ssbPerRAO))){
    //        // current frame and subframe is for this ssb RA
    //        if(raoIndex + (1 / ssbPerRAO) > (accumulationRAO + totalRAOPerSubframe)){
    //            // current subframe can't support all of rao for this ssb
    //            // and last of RAO is mapping to next subframe
    //            printf("cut last\n");
    //        }
    //        if(raoIndex < accumulationRAO){
    //            // current subframe can't support all of rao for this ssb
    //            // and beginning of RAO is mapping to previous subframe
    //            printf("cut beginning\n");

    //        }
    //    }
    //    //if(frameIndex >= raStartFrameIndex 
    //    //        || frameIndex <= raEndFrameIndex){
    //    //    // current frame index is for this ssb index
    //    //    int accumulationRAO = (frameIndex - 1) * totalRAOPerFrame;
    //    //    int i = 0;
    //    //    while(raSubframes.at(i) >= subframeIndex){
    //    //        accumulationRAO += totalRAOPerSubframe;
    //    //    }

    //    //}
    //    //else{
    //    //    printf("current frame isn't for RA\n");
    //    //}
    //}
    //else{
    //    // total need RAO for SSB mapping is less than 1 frame of RAO
    //    // this implies that for all SSB mapping to RAO once
    //    // system needs less than 1 frame to accomplish
    //    // in other words, the total RAO in 1 frame
    //    // maybe can map SSB more than 1 time
    //}
    return false;
}
