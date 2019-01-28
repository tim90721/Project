#ifndef MACROCELL
#define MACROCELL
#include "Cell.h"

class MacroCell : public Cell{
    public:
        MacroCell(int x, int y, int nBeams, CellType cellType);
        void drawCell(QPainter &painter);
        void initializeBeams(int nBeams);
        void setBeamStartAngle(int diffX, int diffY);
        void updateBeamsAngle(int diffX, int diffY);
    private:
        int cellAngle = 120;
};
#endif
