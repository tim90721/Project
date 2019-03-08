#ifndef UE_DEFINE
#define UE_DEFINE

#include <QPainter>
#include <random>
#include "Beam.h"
#include "Cell.h"
#include "IPRACHConfig.h"
#include "IAvailiableRAO.h"
#include "includefile.h"
#include "CommonMath.h"

class Cell;

class UE{
    public:
        UE(int x, int y, int id);
        void setXY(int x, int y);
        void setBeam(int cellIndex, int beamIndex, int beamStrength);
        void receiveSI(Cell *beam);
        void doRA();
        int getX();
        int getY();
        int getID();
        int getBeamIndex();
        int getCellIndex();
        int getBeamStrength();
        bool isBindCell();
        bool isPreambleTransmit();
        void drawUE(QPainter &painter);
        vector<int>& getRAOs();
    private:
        void checkRA();
        void updateRAOforRA();
        void updateRAOforRA(const int startRAO, const int endRAO, const int subframeStartRAO, const int subframeEndRAO, const int totalNeedRAO);
        void storeRAOsforRA(int subframeStartRAO, int subframeEndRAO);
        void transmitMsg1();
        int x;
        int y;
        int id;
        int beamIndex;
        int cellIndex;
        int beamStrength;
        int UEPixelSize;
        int startRAO;
        int endRAO;
        int raStartRAO;
        int raEndRAO;
        bool preambleTransmitted;
        Cell *candidateCell;
        IPRACHConfig *prachConfig;
        IAvailiableRAO *availiableRAO;
        vector<int> raos;
};
#endif
