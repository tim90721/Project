#ifndef BEAM
#define BEAM
#include "includefile.h"
#include <QPainter>
#include "Cell.h"
#include "UE.h"
#include <math.h>
#include "CommonMath.h"

class Cell;

class Beam : public IDrawable{
    private:
        int beamIndex;
        double spanAngle;
        int lengthBeam;
        int cellIndex;
        double startAngle;
        Cell *parent;
    public:
        Beam(Cell *parent, int cellIndex, int beamIndex, int lengthBeam, double spanAngle);
        void draw(QPainter &painter);
        void setBeamIndex(int beamIndex);
        void setSpanAngle(double spanAngle);
        void setStartAngle(int beamIndex, double spanAngle);
        void setStartAngle(double startAngle);
        void setLengthBeam(int lengthBeam);
        void setCellIndex(int cellIndex);
        void detectUE(UE *ue, double power);
        int getX();
        int getY();
        int getBeamIndex();
        double getSpanAngle();
        double getStartAngle();
        int getEndAngle();
        int getLengthBeam();
        int getCellIndex();
};
#endif
