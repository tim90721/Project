#ifndef IAVAILIABLE_RAO
#define IAVAILIABLE_RAO

class IAvailiableRAO{
    public:
        virtual int getNumberofPreambles() = 0;
        virtual int getStartNumberofPreamble(int ssbIndex) = 0;
        virtual int getStartNumberofRAO(int ssbIndex) = 0;
        virtual int getStartRAOofSubframe() = 0;
        virtual int getEndRAOofSubframe() = 0;
        virtual int getTotalNeedRAO() = 0;
        virtual int getTotalRAOPerSubframe() = 0;
        virtual double getSSBPerRAO() = 0;
        virtual bool isRASubframe(const int frameIndex, const int subframeIndex) = 0;
        //virtual bool isAvailiableRAOSubfrom() = 0;
};
#endif
