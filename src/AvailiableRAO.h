#ifndef AVAILIABLE_RAO
#define AVAILIABLE_RAO

#include <stdio.h>
#include "IAvailiable.h"

class AvailiableRAO : IAvailiableRAO{
    private:
        int nSSB;
        int msg1FDM;
        int nPreambles;
        double ssbPerRAO;
        // preamble format?//
    public:
        AvailiableRAO();
        AvailiableRAO(int nRAO, int msg1FDM, int nPreambles, double ssbPerRAO);
        void setNumberofSSB(int nSSB);
        void setMsg1FDM(int msg1FDM);
        void setNumberofPreambles(int nPreambles);
        void setSSBPerRAO(double ssbPerRAO);
        int getNumberofSSB();
        int getMsg1FDM();
        int getNumberofPreambles();
        int getStartNumberofPreamble(int ssbIndex);
        int getStartNumberofRAO(int ssbIndex);
        double getSSBPerRAO();
};
#endif
