#ifndef FEMTOCELL
#define FEMTOCELL
#include "Cell.h"
#include "CommonMath.h"

class FemtoCell : public Cell{
    public:
        FemtoCell(int x, int y, int cellIndex, int nBeams, celltype::CellType cellType, int prachConfigIndex);
        void drawCell(QPainter &painter);
        void initializeBeams();
        void setBeamStartAngle(int diffX, int diffY);
        void updateBeamsAngle(int diffX, int diffY);
};
#endif
