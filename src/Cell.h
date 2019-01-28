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
        Cell(int x, int y, int nBeams, CellType cellType);
        virtual void drawCell(QPainter &painter) = 0;
        void setCellType(CellType cellType);
        void setX(int x);
        void setY(int y);
        void setnBeams(int nBeams);
        void setCellSupportDistance(int supportDistance);
        void setBeamStartAngle(int diffX, int diffY);
        virtual void initializeBeams(int nBeams) = 0;
        virtual void updateBeamsAngle(int diffX, int diffY) = 0;
        int getX();
        int getY();
        int getnBeams();
        int getCellSupportDistance();
        double getBeamStartAngle();
        CellType getCellType();
    protected:
        int x;
        int y;
        int cellSupportDistance;
        double beamStartAngle;
        int nBeams;
        CellType cellType;
        vector<Beam*> beams;
};

#endif
