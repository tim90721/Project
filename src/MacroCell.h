#ifndef MACROCELL
#define MACROCELL
#include "Cell.h"

class MacroCell : public Cell{
    public:
        MacroCell(int x, int y, CellType cellType);
        void drawCell(QPainter &painter);
        void initializeBeams(int nBeams);
    private:
        int cellAngle = 120;
};
#endif
