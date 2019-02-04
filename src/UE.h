#ifndef UE_DEFINE
#define UE_DEFINE

#include <QPainter>
#include "Beam.h"
#include "Cell.h"

class Cell;

class UE{
    public:
        UE(int x, int y, int id);
        void setXY(int x, int y);
        void setBeam(int cellIndex, int beamIndex, int beamStrength);
        void receiveSI(Cell *beam);
        int getX();
        int getY();
        int getID();
        int getBeamIndex();
        int getCellIndex();
        int getBeamStrength();
        void drawUE(QPainter &painter);
    private:
        int x;
        int y;
        int id;
        int beamIndex;
        int cellIndex;
        int beamStrength;
        int UEPixelSize;
        Cell *candidateCell;
};
#endif
