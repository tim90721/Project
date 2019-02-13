#ifndef AVAILIABLE_RAO
#define AVAILIABLE_RAO

#include <stdio.h>
#include "IAvailiable.h"
#include "IPRACHConfig.h"

class AvailiableRAO : IAvailiableRAO{
    private:
        int nSSB;
        int msg1FDM;
        int nPreambles;
        // ssb periodicity for rate matching purpose
        // correspoding to TS 38.331 ssb-periodicityServingCell
        int ssbPeriod;
        int totalRAOPerSubframe;
        int totalRAOPerFrame;
        int totalNeedRAO;   // for all ssb
        double ssbPerRAO;
        IPRACHConfig *prachConfig;
        // preamble format?//
    public:
        AvailiableRAO(int nSSB, double ssbPerRAO, int msg1FDM, int nPreambles, int ssbPeriod, IPRACHConfig *prachConfig);
        void setNumberofSSB(int nSSB);
        void setMsg1FDM(int msg1FDM);
        void setNumberofPreambles(int nPreambles);
        void setSSBPeriod(int ssbPeriod);
        void setSSBPerRAO(double ssbPerRAO);
        int getNumberofSSB();
        int getMsg1FDM();
        int getNumberofPreambles();
        int getSSBPeriod();
        int getStartNumberofPreamble(int ssbIndex);
        int getStartNumberofRAO(int ssbIndex);
        double getSSBPerRAO();
        bool isRASubframe(int frameIndex, int subframeIndex, int ssbIndex);
};
#endif
