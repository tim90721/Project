#ifndef MACROCELL
#define MACROCELL
#include "Cell.h"
#include "CommonMath.h"

class MacroCell : public Cell{
    public:
        MacroCell(int x, int y, int cellIndex, int nBeams, celltype::CellType cellType, int prachConfigIndex, int nPreambles, int cellBW, int ssbSCS, double preambleSCS);
        void draw(QPainter &painter);
        void initializeBeams();
        void setBeamStartAngle(int diffX, int diffY);
        void updateBeamsAngle(int diffX, int diffY);
        ~MacroCell();
};
#endif
