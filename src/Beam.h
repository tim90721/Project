#ifndef BEAM
#define BEAM
#include "includefile.h"
#include <QPainter>
#include "Cell.h"
#include "UE.h"
#include <math.h>
#include "CommonMath.h"

class Cell;

class Beam{
    private:
        int beamIndex;
        int spanAngle;
        //int x;
        //int y;
        int lengthBeam;
        int cellIndex;
        double startAngle;
        double startB;
        double startC;
        double endB;
        double endC;
        Cell *parent;
    public:
        Beam(Cell *parent, int cellIndex, int beamIndex, int lengthBeam, int spanAngle);
        void drawBeam(QPainter &painter);
        //void setX(int x);
        //void setY(int y);
        //void setXY(int x, int y);
        void setBeamIndex(int beamIndex);
        void setSpanAngle(int spanAngle);
        void setStartAngle(int beamIndex, int spanAngle);
        void setStartAngle(double startAngle);
        void setLengthBeam(int lengthBeam);
        void setCellIndex(int cellIndex);
        void findBeamCoverAreaEquation();
        void detectUE(UE *ue, int distance);
        void broadcastSI(UE *ue);
        int getX();
        int getY();
        int getBeamIndex();
        int getSpanAngle();
        double getStartAngle();
        int getEndAngle();
        int getLengthBeam();
        int getCellIndex();
        double getStartB();
        double getStartC();
        double getEndB();
        double getEndC();
};
#endif
