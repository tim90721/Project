#ifndef CELL
#define CELL

#include <QPainter>
#include "includefile.h"
#include "Beam.h"

enum CellType{
    Macro,
    Femto
};

class Cell{
    public:
        Cell(int x, int y, CellType cellType);
        virtual void drawCell(QPainter &painter) = 0;
        void setCellType(CellType cellType);
        void setX(int x);
        void setY(int y);
        void setCellSupportDistance(int supportDistance);
        virtual void initializeBeams(int nBeams) = 0;
        int getX();
        int getY();
        int getCellSupportDistance();
        CellType getCellType();
    protected:
        int x;
        int y;
        int cellSupportDistance;
        CellType cellType;
        vector<Beam*> beams;
};

#endif
