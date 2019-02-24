#ifndef MACROCELL
#define MACROCELL
#include "Cell.h"
#include "CommonMath.h"

class MacroCell : public Cell{
    public:
        MacroCell(int x, int y, int cellIndex, int nBeams, CellType cellType, int prachConfigIndex);
        void drawCell(QPainter &painter);
        void initializeBeams(int nBeams);
        void setBeamStartAngle(int diffX, int diffY);
        void updateBeamsAngle(int diffX, int diffY);
};
#endif
