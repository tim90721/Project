#ifndef UE_DEFINE
#define UE_DEFINE

#include <QPainter>
#include "Beam.h"
#include "Cell.h"
#include "IPRACHConfig.h"
#include "IAvailiableRAO.h"
#include "includefile.h"

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
        void drawUE(QPainter &painter);
    private:
        void checkRA();
        void updateRAOforRA();
        void storeRAOsforRA(int subframeStartRAO, int subframeEndRAO);
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
        Cell *candidateCell;
        IPRACHConfig *prachConfig;
        IAvailiableRAO *availiableRAO;
        vector<int> raos;
};
#endif
