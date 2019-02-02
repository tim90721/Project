#ifndef BEAM
#define BEAM
#include <QPainter>
#include <math.h>

class Beam{
    private:
        int beamIndex;
        int spanAngle;
        int x;
        int y;
        int lengthBeam;
        int cellIndex;
        double startAngle;
        double startB;
        double startC;
        double endB;
        double endC;
    public:
        Beam(int x, int y, int cellIndex, int beamIndex, int lengthBeam, int spanAngle);
        void drawBeam(QPainter &painter);
        void setX(int x);
        void setY(int y);
        void setXY(int x, int y);
        void setBeamIndex(int beamIndex);
        void setSpanAngle(int spanAngle);
        void setStartAngle(int beamIndex, int spanAngle);
        void setStartAngle(double startAngle);
        void setLengthBeam(int lengthBeam);
        void setCellIndex(int cellIndex);
        void findBeamCoverAreaEquation();
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
