#ifndef IAVAILIABLE_RAO
#define IAVAILIABLE_RAO

class IAvailiableRAO{
    public:
        virtual int getNumberofPreambles() = 0;
        virtual int getStartNumberofPreamble(int ssbIndex) = 0;
        virtual int getStartNumberofRAO(int ssbIndex) = 0;
        virtual double getSSBPerRAO() = 0;
        virtual bool isRASubframe(int frameIndex, int subframeIndex, int ssbIndex) = 0;
        //virtual bool isAvailiableRAOSubfrom() = 0;
};
#endif
