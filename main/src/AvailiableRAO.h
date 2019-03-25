#ifndef AVAILIABLE_RAO
#define AVAILIABLE_RAO

#include <stdio.h>
#include "IAvailiableRAO.h"
#include "IPRACHConfig.h"

class AvailiableRAO : public IAvailiableRAO{
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
        int associationPeriod;
        int associationFrame;
        int startRAO;
        int endRAO;
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
        void updateStartandEndRAOofSubframe(const int frameIndex, const int subframeIndex);
        void updateAssociationFrame();
        int getNumberofSSB();
        int getMsg1FDM();
        int getNumberofPreambles();
        int getSSBPeriod();
        int getStartNumberofPreamble(int ssbIndex);
        int getStartNumberofRAO(int ssbIndex);
        int getStartRAOofSubframe();
        int getEndRAOofSubframe();
        int getTotalNeedRAO();
        int getTotalRAOPerSubframe();
        double getSSBPerRAO();
        bool isRASubframe(const int frameIndex, const int subframeIndex);
        ~AvailiableRAO();
};
#endif
